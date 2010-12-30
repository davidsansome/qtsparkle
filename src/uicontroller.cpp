/* This file is part of qtsparkle.
   Copyright (c) 2010 David Sansome <me@davidsansome.com>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
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
