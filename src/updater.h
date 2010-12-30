#ifndef QTSPARKLE_UPDATER_H
#define QTSPARKLE_UPDATER_H

#include <QObject>
#include <QScopedPointer>
#include <QUrl>

class QIcon;
class QNetworkAccessManager;

namespace qtsparkle {

class Updater : public QObject {
  Q_OBJECT

public:
  Updater(const QUrl& appcast_url, QWidget* parent);
  ~Updater();

  void SetNetworkAccessManager(QNetworkAccessManager* network);
  void SetIcon(const QIcon& icon);

public slots:
  void CheckNow();

protected:
  bool event(QEvent* e);

private:
  struct Private;
  QScopedPointer<Private> d;
};

} // namespace qtsparkle


#endif // QTSPARKLE_UPDATER_H
