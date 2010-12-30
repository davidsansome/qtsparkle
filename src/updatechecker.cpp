#include "appcast.h"
#include "compareversions.h"
#include "followredirects.h"
#include "updatechecker.h"

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QtDebug>

namespace qtsparkle {

struct UpdateChecker::Private {
  Private()
    : network_(NULL),
      busy_(false)
  {
  }

  QNetworkAccessManager* network_;
  bool busy_;
};

UpdateChecker::UpdateChecker(QObject* parent)
  : QObject(parent),
    d(new Private)
{
}

UpdateChecker::~UpdateChecker() {
}

void UpdateChecker::SetNetworkAccessManager(QNetworkAccessManager* network) {
  d->network_ = network;
}

void UpdateChecker::Check(const QUrl& appcast_url) {
  qDebug() << __PRETTY_FUNCTION__;

  if (d->busy_)
    return;

  if (!d->network_)
    d->network_ = new QNetworkAccessManager(this);

  d->busy_ = true;

  FollowRedirects* reply = new FollowRedirects(
        d->network_->get(QNetworkRequest(appcast_url)));
  connect(reply, SIGNAL(Finished()), SLOT(Finished()));
  connect(reply, SIGNAL(RedirectLimitReached()), SLOT(RedirectLimitReached()));
}

void UpdateChecker::Finished() {
  qDebug() << __PRETTY_FUNCTION__;

  FollowRedirects* reply = qobject_cast<FollowRedirects*>(sender());
  if (!reply)
    return;
  reply->deleteLater();

  d->busy_ = false;

  AppCastPtr appcast(new AppCast);
  bool success = appcast->Load(reply->reply());
  if (!success) {
    emit CheckFailed(appcast->error_reason());
    return;
  }

  if (!CompareVersions(qApp->applicationVersion(), appcast->version())) {
    emit UpToDate();
    return;
  }

  emit UpdateAvailable(appcast);
}

void UpdateChecker::RedirectLimitReached() {
  emit CheckFailed("Redirect limit reached");
}

} // namespace qtsparkle
