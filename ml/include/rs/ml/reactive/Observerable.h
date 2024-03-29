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

#include <rs/ml/reactive/Observer.h>
#include <set>

namespace rs::ml::reactive
{
  template<typename... Contexts>
  class Observerable
  {
  public:
    void attach(Observer<Contexts...>& observer)
    {
      _observers.insert(&observer);
      observer.onAttached();
    }

    void detach(Observer<Contexts...>& observer)
    {
      _observers.erase(&observer);
      observer.onDetached();
    }

    void insert(Contexts... ctxts)
    {
      for (auto* ob : _observers)
      {
        ob->onInsert(ctxts...);
      }
    }

    void update(Contexts... ctxts)
    {
      for (auto* ob : _observers)
      {
        ob->onUpdate(ctxts...);
      }
    }

    void remove(Contexts... ctxts)
    {
      for (auto* ob : _observers)
      {
        ob->onRemove(ctxts...);
      }
    }

  private:
    std::set<Observer<Contexts...>*> _observers;
  };
}
