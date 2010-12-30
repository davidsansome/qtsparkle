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

#include "uicontroller.h"
#include "updatedialog.h"

#include <QIcon>
#include <QtDebug>

namespace qtsparkle {

struct UiController::Private {
  bool quiet_;
  QWidget* parent_widget_;

  QIcon icon_;

  QScopedPointer<UpdateDialog> dialog_;
};

UiController::UiController(bool quiet, QObject* parent, QWidget* parent_widget)
  : QObject(parent),
    d(new Private)
{
  d->quiet_ = quiet;
  d->parent_widget_ = parent_widget;
}

UiController::~UiController() {
}

void UiController::SetIcon(const QIcon& icon) {
  d->icon_ = icon;
}

void UiController::UpdateAvailable(AppCastPtr appcast) {
  qDebug() << __PRETTY_FUNCTION__;

  d->dialog_.reset(new UpdateDialog(d->parent_widget_));
  d->dialog_->SetIcon(d->icon_);
  d->dialog_->ShowUpdate(appcast);
}

void UiController::UpToDate() {
  qDebug() << "Up to date";
}

void UiController::CheckFailed(const QString& reason) {
  qDebug() << "Check failed:" << reason;
}

} // namespace qtsparkle
