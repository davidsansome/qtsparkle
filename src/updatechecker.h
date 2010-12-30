#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include "appcast.h"

#include <QObject>

class QNetworkAccessManager;
class QUrl;

namespace qtsparkle {

class UpdateChecker : public QObject {
  Q_OBJECT

public:
  UpdateChecker(QObject* parent);
  ~UpdateChecker();

  void SetNetworkAccessManager(QNetworkAccessManager* network);
  void Check(const QUrl& appcast_url);

signals:
  void UpdateAvailable(AppCastPtr appcast);
  void UpToDate();
  void CheckFailed(const QString& reason);

private slots:
  void Finished();
  void RedirectLimitReached();

private:
  struct Private;
  QScopedPointer<Private> d;
};

} // namespace qtsparkle

#endif // UPDATECHECKER_H
