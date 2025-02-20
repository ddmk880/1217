#include <QApplication>
#include <QDir>
#include <QFile>
#include <QMetaType>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QString qss;
//  //qss文件美化
//  QFile qssFile(QDir::currentPath() + "/qss/coffee.qss");
//  qssFile.open(QFile::ReadOnly);
//  if (qssFile.isOpen()) {
//      qss = qssFile.readAll();
//      a.setStyleSheet(qss);
//      qssFile.close();
//  }

  qRegisterMetaType<vector<int>>("vector<int>");
  MainWindow w;
  w.setWindowTitle("地检控制辅助软件_2024.02.20");
  w.showMaximized();
  //全局样式设置
  //a.setStyleSheet("QPushButton { color: red; }");
  //a.setStyleSheet("QWidget{ background-color: beige;");
  //a.setStyleSheet("QWidget{ border-image:url(:/new/prefix1/Pic/aq1.jpg);}");
  return a.exec();
}
