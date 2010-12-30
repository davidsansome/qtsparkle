#include "mainwindow.h"

#include <QApplication>

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  a.setApplicationName("ExampleApp");
  a.setApplicationVersion("2000");

  MainWindow w;
  w.show();

  return a.exec();
}
