#ifndef APPCAST_H
#define APPCAST_H

#include <QScopedPointer>
#include <QSharedPointer>

class QIODevice;

namespace qtsparkle {

class AppCast {
public:
  AppCast();
  ~AppCast();

  bool Load(QIODevice* dev);

  QString version() const;
  QString download_url() const;
  QString release_notes_url() const;

  QString error_reason() const;

private:
  Q_DISABLE_COPY(AppCast)

  struct Private;
  QScopedPointer<Private> d;
};
typedef QSharedPointer<AppCast> AppCastPtr;

} // namespace qtsparkle

#endif // APPCAST_H
