#include "mainwindow.h"

#include <qtsparkle/Updater>

#include <QPushButton>

MainWindow::MainWindow()
  : updater_(new qtsparkle::Updater(QUrl("http://dev.latest.clementine-player.appspot.com/sparkle"), this))
{
  resize(600, 400);

  QPushButton* c = new QPushButton("Check for updates", this);
  c->setGeometry(100, 100, c->sizeHint().width(), c->sizeHint().height());

  QPushButton* e = new QPushButton("Exit", this);
  e->setGeometry(100, 200, e->sizeHint().width(), e->sizeHint().height());

  connect(c, SIGNAL(clicked()), updater_, SLOT(CheckNow()));
  connect(e, SIGNAL(clicked()), SLOT(close()));
}
