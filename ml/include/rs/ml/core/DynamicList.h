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

#include <rs/ml/core/MusicLibrary.h>
#include <rs/ml/core/UpdateObserver.h>
#include <memory>

namespace rs::ml::core
{
  class DynamicList
  {
  public:
    using Filter = std::function<bool(const Track*)>;
    using Value = std::pair<TrackId, const TrackT&>;

    DynamicList(MusicLibrary& ml, Filter filter);
    ~DynamicList();

    std::size_t size() const;
    Value operator[](std::size_t index) const;

    using Observer = UpdateObserver<std::size_t>;
    void attach(Observer& observer);
    void detach(Observer& observer);

  private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
  };
}
