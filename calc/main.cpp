#include <QApplication>

#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile file(":/prefix/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  QPalette palette;
  palette.setColor(QPalette::Window, Qt::white); // Устанавливаем белый цвет фона

  MainWindow w;
  w.setPalette(palette);
  w.setStyleSheet(styleSheet);
  w.setWindowTitle("Engineering Calculator");
  w.show();
  return a.exec();
}
