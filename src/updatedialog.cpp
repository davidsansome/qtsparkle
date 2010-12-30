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

#include "followredirects.h"
#include "updatedialog.h"
#include "ui_updatedialog.h"

#include <QtDebug>

namespace qtsparkle {

struct UpdateDialog::Private {
  Private()
    : network_(NULL)
  {
  }

  QScopedPointer<Ui_UpdateDialog> ui_;

  QNetworkAccessManager* network_;

  static const int kIconSize;
};

const int UpdateDialog::Private::kIconSize = 64;


UpdateDialog::UpdateDialog(QWidget *parent)
  : QDialog(parent),
    d(new Private)
{
  d->ui_.reset(new Ui_UpdateDialog);
  d->ui_->setupUi(this);

  d->ui_->release_notes_label->setText(
      "<b>" + d->ui_->release_notes_label->text() + "</b>");
  d->ui_->icon->hide();
}

UpdateDialog::~UpdateDialog() {
}

void UpdateDialog::SetNetworkAccessManager(QNetworkAccessManager* network) {
  d->network_ = network;
}

void UpdateDialog::SetIcon(const QIcon& icon) {
  if (icon.isNull()) {
    d->ui_->icon->hide();
  } else {
    d->ui_->icon->setPixmap(icon.pixmap(Private::kIconSize));
    d->ui_->icon->show();
  }
}

void UpdateDialog::ShowUpdate(AppCastPtr appcast) {
  d->ui_->title->setText("<h3>" +
      tr("A new version of %1 is available").arg(qApp->applicationName()) + "</h3>");
  d->ui_->summary->setText(
      tr("%1 %2 is now available - you have %3.  Would you like to download it now?")
      .arg(qApp->applicationName(), appcast->version(), qApp->applicationVersion()));

  show();

  if (!d->network_)
    d->network_ = new QNetworkAccessManager(this);

  FollowRedirects* reply = new FollowRedirects(
      d->network_->get(QNetworkRequest(appcast->release_notes_url())));
  connect(reply, SIGNAL(Finished()), SLOT(ReleaseNotesReady()));
}

void UpdateDialog::ReleaseNotesReady() {
  qDebug() << __PRETTY_FUNCTION__;

  FollowRedirects* reply = qobject_cast<FollowRedirects*>(sender());
  if (!reply)
    return;
  reply->deleteLater();

  if (reply->reply()->header(QNetworkRequest::ContentTypeHeader).toString()
      .contains("text/html")) {
    d->ui_->release_notes->setHtml(reply->reply()->readAll());
  } else {
    d->ui_->release_notes->setPlainText(reply->reply()->readAll());
  }

}

} // namespace qtsparkle
