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

#pragma once

#include <rs/ml/core/Track.h>
#include <rs/ml/core/List.h>
#include <rs/ml/core/FlatBuffersStore.h>

namespace rs::ml::core
{
  class MusicLibrary 
  {
  public:
    using TrackStore = FlatBuffersStore<Track>;
    using ListStore = FlatBuffersStore<List>;

    explicit MusicLibrary(const std::string& rootDir);
    TrackStore& tracks() { return _tracks; }
    const TrackStore& tracks() const { return _tracks; }

    ListStore& lists() { return _lists; }
    const ListStore& lists() const { return _lists; }

  private:
    lmdb::env _env;
    TrackStore _tracks;
    ListStore _lists;
  };
}
