#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Controller/controller.h"
#include "../qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT


 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();


 private:
  Ui::MainWindow *ui;
  Controller controller_;
  QMessageBox message;

 private slots:
  void InputX();
  void InputNumbers();
  void InputBinarnOperators();
  void InputUnarnOperators();
  void InputUnarnPlusOrMinus();
  void InputE();
  void Clear();
  void Equal();
  bool CanPlaceCloseBracket();
  bool IsBinarn();
  bool IsDigit();
  bool IsZero();
  bool HasDot();
  void BuildGraph();
};

#endif  // MAINWINDOW_H
