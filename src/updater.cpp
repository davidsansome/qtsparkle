#include "uicontroller.h"
#include "updatechecker.h"
#include "updater.h"

#include <QCoreApplication>
#include <QIcon>
#include <QMessageBox>
#include <QSettings>
#include <QtDebug>


namespace qtsparkle {

struct Updater::Private {
  Private(const QUrl& appcast_url, QWidget* parent_widget, Updater* updater)
    : parent_widget_(parent_widget),
      updater_(updater),
      network_(NULL),
      appcast_url_(appcast_url),
      check_automatically_(false),
      first_boot_(true),
      asked_permission_(false)
  {
  }

  void AskPermission();
  void CheckNow(bool quiet);

  QWidget* parent_widget_;
  Updater* updater_;

  QNetworkAccessManager* network_;
  QIcon icon_;

  QUrl appcast_url_;
  bool check_automatically_;
  bool first_boot_;
  bool asked_permission_;

  QEvent::Type ask_permission_event_;
  QEvent::Type auto_check_event_;

  static const char* kSettingsGroup;
};

const char* Updater::Private::kSettingsGroup = "QtSparkle";


Updater::Updater(const QUrl& appcast_url, QWidget* parent)
  : QObject(parent),
    d(new Private(appcast_url, parent, this))
{
  d->ask_permission_event_ = QEvent::Type(QEvent::registerEventType());
  d->auto_check_event_ = QEvent::Type(QEvent::registerEventType());

  if (parent) {
    SetIcon(parent->windowIcon());
  }

  // Load settings
  QSettings s;
  s.beginGroup(Private::kSettingsGroup);
  d->check_automatically_ = s.value("check_automatically", false).toBool();
  d->first_boot_ = s.value("first_boot", true).toBool();
  d->asked_permission_ = s.value("asked_permission", false).toBool();

  // Should we ask for permission now?
  if (!d->asked_permission_ && !d->first_boot_) {
    QCoreApplication::postEvent(this, new QEvent(d->ask_permission_event_));
  }

  // Or check for updates?
  if (d->check_automatically_) {
    QCoreApplication::postEvent(this, new QEvent(d->auto_check_event_));
  }

  // Turn off the first boot flag if it's on
  if (d->first_boot_) {
    d->first_boot_ = false;
    s.setValue("first_boot", false);
  }
}

Updater::~Updater() {
}

void Updater::SetIcon(const QIcon& icon) {
  d->icon_ = icon;
}

void Updater::SetNetworkAccessManager(QNetworkAccessManager* network) {
  d->network_ = network;
}

bool Updater::event(QEvent* e) {
  if (e->type() == d->auto_check_event_) {
    d->CheckNow(true);
    return true;
  }

  if (e->type() == d->ask_permission_event_) {
    d->AskPermission();
    return true;
  }

  return QObject::event(e);
}

void Updater::Private::AskPermission() {
  QMessageBox box(QMessageBox::Question,
    tr("Check for updates automatically?"),
    tr("Should %1 automatically check for updates?  You can always check for updates manually from the menu.")
        .arg(qApp->applicationName()), QMessageBox::NoButton, parent_widget_);
  box.addButton(tr("Check automatically"), QMessageBox::YesRole);
  box.addButton(tr("Don't check"), QMessageBox::NoRole);

  check_automatically_ = (box.exec() == QDialog::Accepted);

  QSettings s;
  s.beginGroup(Private::kSettingsGroup);
  s.setValue("asked_permission", true);
  s.setValue("check_automatically", check_automatically_);

  if (check_automatically_) {
    CheckNow(true);
  }
}

void Updater::CheckNow() {
  d->CheckNow(false);
}

void Updater::Private::CheckNow(bool quiet) {
  UiController* controller = new UiController(quiet, updater_, parent_widget_);
  controller->SetIcon(icon_);

  UpdateChecker* checker = new UpdateChecker(updater_);
  checker->SetNetworkAccessManager(network_);

  connect(checker, SIGNAL(CheckFailed(QString)), controller, SLOT(CheckFailed(QString)));
  connect(checker, SIGNAL(UpdateAvailable(AppCastPtr)), controller, SLOT(UpdateAvailable(AppCastPtr)));
  connect(checker, SIGNAL(UpToDate()), controller, SLOT(UpToDate()));

  checker->Check(appcast_url_);
}

} // namespace qtsparkle
