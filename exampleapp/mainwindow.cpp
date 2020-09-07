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

#include "mainwindow.h"

#if QT_VERSION < QT_VERSION_CHECK( 5, 0, 0 )
#include <qtsparkle/Updater>
#elif QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
#include <qtsparkle-qt5/Updater>
#else
#include <qtsparkle-qt6/Updater>
#endif

#include <QPushButton>
#include <QUrl>

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
