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

#include "AddTrackDialog.h"

AddTrackDialog::AddTrackDialog(QWidget *parent, Qt::WindowFlags f)
  : QDialog{parent, f}
{
  setupUi(this);
}

rs::ml::core::TrackT AddTrackDialog::track() const
{
  rs::ml::core::TrackT t;
  //t.title = lineEditTitle->text().toStdString();
  //t.artist = lineEditArtist->text().toStdString();
  //t.album = lineEditAlbum->text().toStdString();
  return t;
}
