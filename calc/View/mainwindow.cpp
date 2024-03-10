#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);
  connect(ui->number_0, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_1, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_2, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_3, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_4, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_5, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_6, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_7, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_8, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_9, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(InputNumbers()));
  connect(ui->number_x, SIGNAL(clicked()), this, SLOT(InputX()));
  connect(ui->button_exp, SIGNAL(clicked()), this, SLOT(InputE()));

  connect(ui->button_add, SIGNAL(clicked()), this,
          SLOT(InputBinarnOperators()));
  connect(ui->button_sub, SIGNAL(clicked()), this,
          SLOT(InputBinarnOperators()));
  connect(ui->button_mult, SIGNAL(clicked()), this,
          SLOT(InputBinarnOperators()));
  connect(ui->button_div, SIGNAL(clicked()), this,
          SLOT(InputBinarnOperators()));
  connect(ui->button_mod, SIGNAL(clicked()), this,
          SLOT(InputBinarnOperators()));
  connect(ui->button_pow, SIGNAL(clicked()), this,
          SLOT(InputBinarnOperators()));
  connect(ui->button_close_bracket, SIGNAL(clicked()), this,
          SLOT(InputBinarnOperators()));

  connect(ui->button_sin, SIGNAL(clicked()), this, SLOT(InputUnarnOperators()));
  connect(ui->button_cos, SIGNAL(clicked()), this, SLOT(InputUnarnOperators()));
  connect(ui->button_tan, SIGNAL(clicked()), this, SLOT(InputUnarnOperators()));
  connect(ui->button_asin, SIGNAL(clicked()), this,
          SLOT(InputUnarnOperators()));
  connect(ui->button_acos, SIGNAL(clicked()), this,
          SLOT(InputUnarnOperators()));
  connect(ui->button_atan, SIGNAL(clicked()), this,
          SLOT(InputUnarnOperators()));
  connect(ui->button_sqrt, SIGNAL(clicked()), this,
          SLOT(InputUnarnOperators()));
  connect(ui->button_ln, SIGNAL(clicked()), this, SLOT(InputUnarnOperators()));
  connect(ui->button_log, SIGNAL(clicked()), this, SLOT(InputUnarnOperators()));
  connect(ui->button_open_bracket, SIGNAL(clicked()), this,
          SLOT(InputUnarnOperators()));
  connect(ui->button_unarn, SIGNAL(clicked()), this,
          SLOT(InputUnarnPlusOrMinus()));

  connect(ui->button_clear, SIGNAL(clicked()), this, SLOT(Clear()));
  connect(ui->button_equal, SIGNAL(clicked()), this, SLOT(Equal()));
  connect(ui->button_build_graph, SIGNAL(clicked()), this, SLOT(BuildGraph()));

  ui->xmin_spinbox->setValue(-10);
  ui->xmax_spinbox->setValue(10);
  ui->ymin_spinbox->setValue(-10);
  ui->ymax_spinbox->setValue(10);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::IsBinarn() {
  QString expression = ui->expression_line->text();
  bool res = false;

  if (expression.endsWith("+") || expression.endsWith("-") ||
      expression.endsWith("*") || expression.endsWith("/") ||
      expression.endsWith("^") || expression.endsWith("%"))
    res = true;
  return res;
}

bool MainWindow::IsDigit() {
  QString expression = ui->expression_line->text();
  bool res = false;

  if (expression.endsWith("0") || expression.endsWith("1") ||
      expression.endsWith("2") || expression.endsWith("3") ||
      expression.endsWith("4") || expression.endsWith("5") ||
      expression.endsWith("6") || expression.endsWith("7") ||
      expression.endsWith("8") || expression.endsWith("9"))
    res = true;
  return res;
}

bool MainWindow::HasDot() {
  std::string expression = ui->expression_line->text().toStdString();
  short index = expression.length() - 1;

  while (std::isdigit(expression[index]) || expression[index] == '.') {
    if (expression[index] == '.') return true;
    index--;
  }
  return false;
}

bool MainWindow::IsZero() {
  std::string str = ui->expression_line->text().toStdString();
  bool res = false;
  short counter = 0;
  short index = str.length() - 1;

  while (std::isdigit(str[index]) || str[index] == '.') {
    counter++;
    index--;
  }
  if (counter == 1 && str[str.length() - 1] == '0') res = true;
  return res;
}

bool MainWindow::CanPlaceCloseBracket() {
  std::string str = ui->expression_line->text().toStdString();
  bool res = false;

  if (std::count(str.begin(), str.end(), '(') >
      std::count(str.begin(), str.end(), ')'))
    res = true;
  return res;
}

void MainWindow::InputNumbers() {
  QPushButton *button = (QPushButton *)sender();
  QString expression = ui->expression_line->text();

  if (!expression.endsWith(")") && !expression.endsWith("x") &&
      !expression.endsWith("E")) {
    if (button->text() == "." && !HasDot() && IsDigit() &&
        !expression.endsWith("x"))
      ui->expression_line->setText(expression + button->text());
    if (button->text() != ".")
      if (!IsZero()) ui->expression_line->setText(expression + button->text());
  }
}

void MainWindow::InputE() {
  QPushButton *button = (QPushButton *)sender();
  QString expression = ui->expression_line->text();

  if (IsDigit() && !expression.endsWith("E"))
    ui->expression_line->setText(expression + button->text());
}

void MainWindow::InputX() {
  QPushButton *button = (QPushButton *)sender();
  QString expression = ui->expression_line->text();

  if (button->text() == "x")
    if (!expression.endsWith("x") && !IsDigit() && !expression.endsWith(".") &&
        !expression.endsWith("E"))
      ui->expression_line->setText(expression + button->text());
}

void MainWindow::InputBinarnOperators() {
  QPushButton *button = (QPushButton *)sender();
  QString expression = ui->expression_line->text();

  if (expression.endsWith("E") &&
      (button->text() == "+" || button->text() == "-"))
    ui->expression_line->setText(expression + button->text());
  if (!expression.endsWith("(") && !IsBinarn() && expression != "" &&
      !expression.endsWith(".") && !expression.endsWith("E")) {
    if (button->text() == ")") {
      if (CanPlaceCloseBracket())
        ui->expression_line->setText(expression + button->text());
    } else
      ui->expression_line->setText(expression + button->text());
  }
}

void MainWindow::InputUnarnOperators() {
  QPushButton *button = (QPushButton *)sender();
  QString expression = ui->expression_line->text();

  if (!expression.endsWith(")") && !IsDigit() && !expression.endsWith(".") &&
      !expression.endsWith("x") && !expression.endsWith("E")) {
    if (button->text() == "(")
      ui->expression_line->setText(expression + button->text());
    else
      ui->expression_line->setText(expression + button->text() + "(");
  }
}

void MainWindow::InputUnarnPlusOrMinus() {
  QPushButton *button = (QPushButton *)sender();
  QString expression = ui->expression_line->text();

  if (expression.endsWith("(") || IsBinarn() || expression.isEmpty()) {
      if (!expression.endsWith("E")) {
        if (expression.endsWith("("))
          ui->expression_line->setText(expression + button->text().front());
        else
          ui->expression_line->setText(expression + "(" + button->text().front());
      }
  }
}

void MainWindow::Clear() { ui->expression_line->setText(""); }

void MainWindow::Equal() {
  std::string str = ui->expression_line->text().toStdString();
  double x = ui->x_input->value();

  if (controller_.Validate(str)) try {
      ui->result_line->setText(
          QString::number(controller_.Calculate(str, x), 'f', 7));
      ui->expression_line->setText("");
    } catch (const std::invalid_argument &e) {
      message.setText(e.what());
      message.exec();
    }
  else
    ui->result_line->setText("Error in expression");
}

void MainWindow::BuildGraph() {
  QVector<double> x, y;
  std::vector<double> x_reserve, y_reserve;
  double xmin, xmax, ymin, ymax;
  QString str = ui->expression_line->text();

  if (str.contains("x")) {
    xmin = ui->xmin_spinbox->value();
    xmax = ui->xmax_spinbox->value();
    ymin = ui->ymin_spinbox->value();
    ymax = ui->ymax_spinbox->value();

    x_reserve = controller_.GetCoordinateX(xmin, xmax);
    y_reserve = controller_.GetCoordinateY(str.toStdString(), xmin, xmax);
    x = QVector<double>(x_reserve.begin(), x_reserve.end());
    y = QVector<double>(y_reserve.begin(), y_reserve.end());

    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget->graph(0)->addData(x, y);
    ui->widget->xAxis->setRange(xmin, xmax);
    ui->widget->yAxis->setRange(ymin, ymax);
    ui->widget->replot();
    x.clear();
    y.clear();
    ui->widget->graph(0)->data()->clear();
  } else {
    message.setText("Need X");
    message.exec();
  }
}
