#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace qtsparkle {
  class Updater;
}

class MainWindow : public QWidget {
public:
  MainWindow();

private:
  qtsparkle::Updater* updater_;
};

#endif
