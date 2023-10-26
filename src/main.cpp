#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon("./images/favicon.ico"));
//  a.setWindowIcon(QIcon(":/icons/favicon"));

  MainWindow w;
  w.show();
  return a.exec();
}

