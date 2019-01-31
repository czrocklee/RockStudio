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

#include "ListCommand.h"
#include <rs/ml/core/List.h>
#include <rs/ml/core/Track.h>
#include <rs/ml/query/Parser.h>
#include <rs/ml/query/Serializer.h>
#include <rs/cli/BasicCommand.h>

#include <iomanip>

namespace
{
  namespace bpo = boost::program_options;
  using namespace rs::ml;

  std::string list(core::MusicLibrary& ml, core::ListId id = core::InvalidListId)
  {
    std::ostringstream oss;

    if (id != core::InvalidListId)
    {
      auto txn = ml.lists().readTransaction();
      const core::List* list = txn[id];
      oss << std::setw(5) << id;
      oss << std::setw(10) << list->name() << std::setw(50) << list->expr() << std::setw(50) << list->desc() << std::endl;
      return oss.str();
    }

    for (const auto& l: ml.lists().readTransaction())
    {
      oss << std::setw(5) << l.first;
      oss << std::setw(10) << l.second->name() << std::setw(50) << l.second->expr() << std::setw(50) << l.second->desc() << std::endl;
    }

    return oss.str();
  }

  std::string create(core::MusicLibrary& ml, const std::string& name, const std::string& expr, const std::string& desc)
  {
    auto expression = query::parse(expr);
    query::normalize(expression);
    std::string exprStr = query::serialize(expression);
    auto txn = ml.lists().writeTransaction();

    auto id = txn.create([&name, &exprStr, &desc] (flatbuffers::FlatBufferBuilder& fbb) 
    {
      return core::CreateListDirect(fbb, name.c_str(), exprStr.c_str(), desc.c_str());
    });

    txn.commit();
    return list(ml, id);
  }

  std::string del(core::MusicLibrary& ml, core::ListId id)
  {
    auto txn = ml.lists().writeTransaction();
    txn.del(id);
    txn.commit();
    return {};
  }
 
}

namespace rs::rml
{
  ListCommand::ListCommand(ml::core::MusicLibrary& ml) 
    : _ml{ml}
  {
    addCommand<rs::cli::BasicCommand>("list", [this](const auto& vm) { return list(_ml); });

    addCommand<rs::cli::BasicCommand>("create")
      .addOption("name, n", bpo::value<std::string>()->required(), "list name", 1)
      .addOption("filter, f", bpo::value<std::string>()->required(), "track filter expression", 1)
      .addOption("desc, d", bpo::value<std::string>(), "list description", 1)
      .setExecutor([this](const auto& vm) { return ""; }); // create(this->_ml, vm["name"].as<std::string>(), vm["filter"].as<std::string>(), vm["desc"].as<std::string>()); });

    addCommand<rs::cli::BasicCommand>("delete")
      .addOption("id", bpo::value<rs::ml::core::ListId>()->required(), "list id", 1);
 //     .setExecutor([this](const auto& vm) { del(_ml, vm["id"].as<core::ListId>()); });
  }
}