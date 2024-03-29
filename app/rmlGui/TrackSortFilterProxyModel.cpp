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

#include "TrackSortFilterProxyModel.h"
#include <rs/ml/expr/Evaluator.h>
#include <rs/ml/expr/Parser.h>
//#include <QtConcurrent>


/* TrackSortFilterProxyModel::TrackSortFilterProxyModel(rs::ml::core::MusicLibrary& ml, QObject *parent)
  : QSortFilterProxyModel{parent}, _ml{ml}
{
} */

void TrackSortFilterProxyModel::onQuickFilterChanged(const QString& filter)
{
  _quick = filter.toStdString();
  /*
  if (filter.isEmpty())
  {
    _filter.reset();
  }
  else
 
    _filter = rs::ml::query::TrackFilter{filter.toStdString()};
  }*/

  invalidateFilter();
}
#include <QtCore/QDebug>
bool TrackSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
  if (_quick.empty())
  {
    return true;
  }
  else
  {
    auto index = sourceModel()->index(sourceRow, 0);
    using IdTrackPair = std::pair<rs::ml::core::MusicLibrary::TrackId, rs::ml::fbs::TrackT>;
    const auto& track = static_cast<IdTrackPair*>(index.internalPointer())->second;

    return track.meta->title.find(_quick) != std::string::npos || 
           track.meta->album.find(_quick) != std::string::npos ||
           track.meta->artist.find(_quick) != std::string::npos;
    /*
    auto index = sourceModel()->index(sourceRow, 0);
    auto reader = _ml.reader();
    auto track = reader[static_cast<rs::ml::core::TrackId>(index.internalId())];
    return std::invoke(_filter.value(), track);*/
  }
}
