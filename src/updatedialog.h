/* This file is part of Clementine.
   Copyright 2010, David Sansome <me@davidsansome.com>

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include "appcast.h"

#include <QDialog>

class Ui_UpdateDialog;

class QNetworkAccessManager;

namespace qtsparkle {

class UpdateDialog : public QDialog {
  Q_OBJECT

public:
  UpdateDialog(QWidget* parent = 0);
  ~UpdateDialog();

  void SetNetworkAccessManager(QNetworkAccessManager* network);
  void SetIcon(const QIcon& icon);

public slots:
  void ShowUpdate(AppCastPtr appcast);

private slots:
  void ReleaseNotesReady();

private:
  struct Private;
  QScopedPointer<Private> d;
};

} // namespace qtsparkle

#endif // UPDATEDIALOG_H
