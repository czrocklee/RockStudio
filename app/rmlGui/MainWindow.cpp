/*
 * Copyright (C) <year> <name of author>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"
#include "AddTrackDialog.h"
#include "NewListDialog.h"
#include "TableModel.h"
#include "TrackSortFilterProxyModel.h"

#include <rs/ml/reactive/ItemList.h>
#include <rs/ml/expr/Evaluator.h>
#include <rs/ml/expr/Parser.h>
#include <QtCore/QDebug>
#include <QtWidgets/QFileDialog>
#include <QtCore/QSettings>
#include <filesystem>

// using TrackList = rs::ml::reactive::ItemList<rs::ml::core::MusicLibrary::TrackId, rs::ml::fbs::TrackT>;

MainWindow::MainWindow()
{
  setupUi(this);

  connect(actionOpen, &QAction::triggered, [this] {
    if (QString dir = QFileDialog::getExistingDirectory(
          this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        !dir.isNull())
    {
      openMusicLibrary(dir.toStdString());
    }
  });

  if (auto lastSession = QSettings{"settings.ini"}.value("session.lastMusicLibaryOpened");
      !lastSession.isNull() && std::filesystem::exists({lastSession.toString().toStdString()}))
  {
    openMusicLibrary(lastSession.toString().toStdString());
  }
}

void MainWindow::openMusicLibrary(const std::string& dir)
{
  _ml = std::make_unique<MusicLibrary>(dir);

  auto txn = _ml->readTransaction();
  loadTracks(txn);
  loadLists(txn);
  QSettings settings{"settings.ini"};
  settings.setValue("session.lastMusicLibaryOpened", QString::fromStdString(dir));
}

void MainWindow::loadTracks(ReadTransaction& txn)
{
  for (auto [id, track] : _ml->tracks().reader(txn))
  {
    auto cstr = [](const flatbuffers::String* str) { return str == nullptr ? "nil" : str->str(); };

    //std::cout << cstr(track->meta()->album());
    rs::ml::fbs::TrackT tt;
    track->UnPackTo(&tt);
    _allTracks.insert(id, std::move(tt));
  }
}

void MainWindow::loadLists(ReadTransaction& txn)
{
  auto* all = new ListItem{"all", listWidget};
  all->trackView = new TrackView{_allTracks, stackedWidget};
  stackedWidget->addWidget(all->trackView);
  connect(
    all->trackView->tableView, &QAbstractItemView::clicked, [this](const QModelIndex& index) { this->onTrackClicked(index); });

  for (const auto [_, list] : _ml->lists().reader(txn))
  {
    addListItem(list);
  }

  connect(listWidget, &QListWidget::currentItemChanged, [this](auto* curr, auto*) {
    stackedWidget->setCurrentWidget(dynamic_cast<ListItem*>(curr)->trackView);
  });

  listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(listWidget, &QListWidget::customContextMenuRequested, [this](QPoint pos) {
    // Handle global position
    QPoint globalPos = listWidget->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("New", [this] {
      if (auto* dialog = new NewListDialog{this}; dialog->exec())
      {
        auto txn = _ml->writeTransaction();
        auto writer = _ml->lists().writer(txn);
        auto [_, list] = writer.createT(dialog->list());
        addListItem(list);
        txn.commit();
      }
    });
    myMenu.addAction("Delete", this, SLOT(eraseItem()));

    // Show context menu at handling position
    myMenu.exec(globalPos);
  });
}

void MainWindow::onTrackClicked(const QModelIndex& index)
{
  if (QVariant resourceId = index.model()->data(index, Qt::UserRole); resourceId.isValid())
  {
    auto txn = _ml->readTransaction();
    auto data = _ml->resources().reader(txn)[resourceId.toULongLong()];

    if (QPixmap pix; pix.loadFromData(static_cast<const uchar*>(data.data()), data.size(), "JPG"))
    {
      coverArtLabel->setPixmap(pix);
    }
  }
  else
  {
    Q_INIT_RESOURCE(resources);
    coverArtLabel->setPixmap(QPixmap{":/images/nocoverart.jpg"});
  }
}

void MainWindow::addListItem(const rs::ml::fbs::List* list)
{
  auto* listItem = new ListItem{QString::fromUtf8(list->name()->c_str()), listWidget};
  listItem->tracks =
    std::make_unique<TrackFilterList>(_allTracks, [expr = rs::ml::expr::parse(list->expr()->c_str())](const auto& tt) {
      return rs::ml::expr::toBool(rs::ml::expr::evaluate(expr, tt));
    });
  listItem->trackView = new TrackView{*listItem->tracks, stackedWidget};
  stackedWidget->addWidget(listItem->trackView);
  connect(listItem->trackView->tableView, &QAbstractItemView::clicked, [this](const QModelIndex& index) {
    this->onTrackClicked(index);
  });
}