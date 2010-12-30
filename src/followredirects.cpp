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

namespace qtsparkle {

struct FollowRedirects::Private {
  Private()
    : reply_(NULL),
      redirect_count_(0)
  {
  }

  QNetworkReply* reply_;
  int redirect_count_;

  static const int kMaxRedirects = 5;
};

FollowRedirects::FollowRedirects(QNetworkReply* reply)
  : d(new Private)
{
  d->reply_ = reply;
  connect(reply, SIGNAL(finished()), SLOT(FinishedSlot()));
}

FollowRedirects::~FollowRedirects() {
  delete d->reply_;
}

QNetworkReply* FollowRedirects::reply() const {
  return d->reply_;
}

void FollowRedirects::FinishedSlot() {
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  if (!reply || reply != d->reply_)
    return;

  QVariant redirect_target = reply->attribute(
        QNetworkRequest::RedirectionTargetAttribute);
  if (redirect_target.isValid()) {
    reply->deleteLater();

    if (d->redirect_count_ >= Private::kMaxRedirects) {
      d->reply_ = NULL;
      emit RedirectLimitReached();
      return;
    }

    d->redirect_count_ ++;

    QUrl target = redirect_target.toUrl();
    if (target.scheme().isEmpty() || target.host().isEmpty()) {
      QString path = target.path();
      target = reply->url();
      target.setPath(path);
    }

    d->reply_ = d->reply_->manager()->get(QNetworkRequest(target));
    connect(d->reply_, SIGNAL(finished()), SLOT(FinishedSlot()));
    return;
  }

  emit Finished();
}

} // namespace qtsparkle
