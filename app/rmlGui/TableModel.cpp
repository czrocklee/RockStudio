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

#include "TableModel.h"
#include <iostream>
#include <boost/algorithm/string/join.hpp>
#include <QtCore/QDebug>

//using IdTrackPair = TableModel::IdTrackPair;
using AbstractTrackList = TableModel::AbstractTrackList;

struct TableModelPrivate : AbstractTrackList::Observer
{
  Q_DECLARE_PUBLIC(TableModel)

  TableModelPrivate(TableModel* q, AbstractTrackList& tracks) : q_ptr{q}, tracks{tracks} { tracks.attach(*this); }

  ~TableModelPrivate()
  {
    // tracks.detach(*this);
  }

  void onInsert(TableModel::TrackId, const rs::ml::fbs::TrackT&, AbstractTrackList::Index index) override
  {
    Q_Q(TableModel);
    q->beginInsertRows({}, index, index);
    q->endInsertRows();
  }
  void onUpdate(TableModel::TrackId, const rs::ml::fbs::TrackT&, AbstractTrackList::Index index) override
  {
    Q_Q(TableModel);
    emit(q->dataChanged(q->index(index, 0, {}), q->index(index, 2, {})));
  }

  void onRemove(TableModel::TrackId, const rs::ml::fbs::TrackT&, AbstractTrackList::Index index) override
  {
    Q_Q(TableModel);
    q->beginRemoveRows({}, index, index);
    q->endRemoveRows();
  }

  TableModel* q_ptr;
  AbstractTrackList& tracks;
};

TableModel::TableModel(QObject* parent) : QAbstractTableModel(parent) {}

TableModel::TableModel(AbstractTrackList& tracks, QObject* parent)
  : QAbstractTableModel{parent}, d_ptr{std::make_unique<TableModelPrivate>(this, tracks)}
{}

TableModel::~TableModel() {}

int TableModel::rowCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return d_ptr->tracks.size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
  Q_UNUSED(parent);
  return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= static_cast<int>(d_ptr->tracks.size()) || index.row() < 0)
    return QVariant();

  const auto& track = d_ptr->tracks.at(AbstractTrackList::Index{static_cast<std::size_t>(index.row())}).second;

  if (role == Qt::DisplayRole)
  {
    if (index.column() == 0)
      return QString::fromUtf8(track.meta->artist.c_str());
    else if (index.column() == 1)
      return QString::fromUtf8(track.meta->album.c_str());
    else if (index.column() == 2)
      return QString::fromUtf8(track.meta->title.c_str());
    else if (index.column() == 3)
    {
      QStringList tags;
      std::transform(track.tags.begin(), track.tags.end(), std::back_inserter(tags), [](const auto& tag) { return QString::fromUtf8(tag.c_str()); });
      return tags;
    }
  }

  if (role == Qt::UserRole && !track.rsrc.empty())
  {
    return static_cast<qulonglong>(track.rsrc.front()->id);
  }

  return {};
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
    return QVariant();

  if (orientation == Qt::Horizontal)
  {
    switch (section)
    {
      case 0: return tr("Artist");
      case 1: return tr("Album");
      case 2: return tr("Title");
      case 3: return tr("Tags");

      default: return QVariant();
    }
  }
  return QVariant();
}
//! [3]

//! [4]
bool TableModel::insertRows(int position, int rows, const QModelIndex& index)
{
  Q_UNUSED(index);
  beginInsertRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    //       _list.insert(position, { QString(), QString() });

    endInsertRows();
  return true;
}
//! [4]

//! [5]
bool TableModel::removeRows(int position, int rows, const QModelIndex& index)
{
  Q_UNUSED(index);
  beginRemoveRows(QModelIndex(), position, position + rows - 1);

  for (int row = 0; row < rows; ++row)
    //       _list.removeAt(position);

    endRemoveRows();
  return true;
}
//! [5]

//! [6]
bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
  /*   if (index.isValid() && role == Qt::EditRole)
    {
      std::cout << "setData " << index.row() << ' ' << index.column() << std::endl;
      int row = index.row();

      auto track = rs::ml::core::clone(_list[row].second);
      if (index.column() == 0)
      {
        track.artist = value.toString().toStdString();
      } else if (index.column() == 1)
      {
        track.album = value.toString().toStdString();
      } else if (index.column() == 2)
      {
        track.title = value.toString().toStdString();
      } else
      {
        return false;
      }

      _list.mutate(row, track);

      return true;
    } */

  return false;
}
//! [6]

//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QModelIndex TableModel::index(int row, int column, const QModelIndex& parent) const
{

  return createIndex(
    row, column, &const_cast<AbstractTrackList::Value&>(d_ptr->tracks.at(AbstractTrackList::Index{static_cast<std::size_t>(row)})));
}

/* void TableModel::onQuickFilterChanged(const QString& filter)
{

  beginResetModel();
  rs::ml::query::TrackFilter f{filter.toStdString()};
//  auto future = QtConcurrent::filtered(_allTracks, f);
//  future.waitForFinished();
//  _list = future.results();


  _list.clear();
  for (auto pair : _ml.reader())
  {
    if (f(pair.second))
    {
      _list.append(pair.first);
    }
  }


  endResetModel();
} */
