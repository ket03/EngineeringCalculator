#include "model.h"

Model::Operation Model::get_enum_type(std::string expression, short index) {
  Operation res = None;
  if (expression[index] == '(') res = OpenBracket;
  if (expression[index] == ')') res = CloseBracket;
  if (expression[index] == '+') res = Add;
  if (expression[index] == '-') res = Sub;
  if (expression[index] == '*') res = Mult;
  if (expression[index] == '/') res = Div;
  if (expression[index] == 'm') res = Mod;
  if (expression[index] == '^') res = Pow;
  if (expression[index] == 'l' && expression[index + 1] == 'n') res = Ln;
  if (expression[index] == 'l' && expression[index + 1] == 'o') res = Log;
  if (expression[index] == 's' && expression[index + 1] == 'i') res = Sin;
  if (expression[index] == 's' && expression[index + 1] == 'q') res = Sqrt;
  if (expression[index] == 'c' && expression[index + 1] == 'o') res = Cos;
  if (expression[index] == 't' && expression[index + 1] == 'a') res = Tan;
  if (expression[index] == 'a' && expression[index + 1] == 's') res = Asin;
  if (expression[index] == 'a' && expression[index + 1] == 'c') res = Acos;
  if (expression[index] == 'a' && expression[index + 1] == 't') res = Atan;
  if (expression[index] == '~') res = UnarnMinus;
  return res;
}

short Model::get_length(Operation operation) {
  short res = 1;
  if (operation == Ln) res = 2;
  if (operation == Log || operation == Sin || operation == Cos ||
      operation == Tan || operation == Mod)
    res = 3;
  if (operation == Sqrt || operation == Asin || operation == Acos ||
      operation == Atan)
    res = 4;
  return res;
}

short Model::get_priority(std::string expression, short index) {
  short priority;
  if (expression[index] == '(' || expression[index] == ')') priority = 0;
  if (expression[index] == '+' || expression[index] == '-') priority = 1;
  if (expression[index] == '*' || expression[index] == '/' ||
      expression[index] == 'm')
    priority = 2;
  if (expression[index] == '^') priority = 3;
  if (expression[index] == 'l' &&
      (expression[index + 1] == 'o' || expression[index + 1] == 'n'))
    priority = 4;
  if (expression[index] == 's' &&
      (expression[index + 1] == 'i' || expression[index + 1] == 'q'))
    priority = 4;
  if (expression[index] == 'c' && expression[index + 1] == 'o') priority = 4;
  if (expression[index] == 't' && expression[index + 1] == 'a') priority = 4;
  if (expression[index] == 'a' &&
      (expression[index + 1] == 's' || expression[index + 1] == 'c' ||
       expression[index + 1] == 't'))
    priority = 4;
  if (expression[index] == '~') priority = 5;
  return priority;
}

Model::Leksema Model::AddElement(std::string expression, short index) {
  Leksema element;
  element.operation = get_enum_type(expression, index);
  element.priority = get_priority(expression, index);
  return element;
}

short Model::IsUnarnOrBinarn(Operation operation) {
  short res = 0;
  if (operation == Add || operation == Sub || operation == Mult ||
      operation == Div || operation == Pow || operation == Mod)
    res = 2;
  if (operation == Ln || operation == Log || operation == Sin ||
      operation == Cos || operation == Tan || operation == Asin ||
      operation == Acos || operation == Atan || operation == Sqrt ||
      operation == UnarnMinus)
    res = 1;
  return res;
}

void Model::CalculateBinarn(std::stack<double>& Stack_digits,
                            std::stack<Leksema>& Stack_operators) {
  double first_value = Stack_digits.top();
  Stack_digits.pop();
  double second_value = Stack_digits.top();
  Stack_digits.pop();
  if (Stack_operators.top().operation == Add)
    Stack_digits.push(second_value + first_value);
  if (Stack_operators.top().operation == Sub)
    Stack_digits.push(second_value - first_value);
  if (Stack_operators.top().operation == Mult)
    Stack_digits.push(second_value * first_value);
  if (Stack_operators.top().operation == Div) {
    if (first_value == 0) throw std::invalid_argument("can't divide by zero");
    Stack_digits.push(second_value / first_value);
  }
  if (Stack_operators.top().operation == Mod)
    Stack_digits.push(std::fmod(second_value, first_value));
  if (Stack_operators.top().operation == Pow)
    Stack_digits.push(std::pow(second_value, first_value));
  Stack_operators.pop();
}

void Model::CalculateUnarn(std::stack<double>& Stack_digits,
                           std::stack<Leksema>& Stack_operators) {
  double value = Stack_digits.top();
  Stack_digits.pop();
  if (Stack_operators.top().operation == Ln) Stack_digits.push(std::log(value));
  if (Stack_operators.top().operation == Log)
    Stack_digits.push(std::log10(value));
  if (Stack_operators.top().operation == Sin)
    Stack_digits.push(std::sin(value));
  if (Stack_operators.top().operation == Cos)
    Stack_digits.push(std::cos(value));
  if (Stack_operators.top().operation == Tan)
    Stack_digits.push(std::tan(value));
  if (Stack_operators.top().operation == Asin) {
    if (value > 1 || value < -1)
      throw std::invalid_argument(
          "value in asin or acos must be in range[-1; 1]");
    Stack_digits.push(std::asin(value));
  }
  if (Stack_operators.top().operation == Acos) {
    if (value > 1 || value < -1)
      throw std::invalid_argument(
          "value in asin or acos must be in range[-1; 1]");
    Stack_digits.push(std::acos(value));
  }
  if (Stack_operators.top().operation == Atan)
    Stack_digits.push(std::atan(value));
  if (Stack_operators.top().operation == Sqrt) {
    if (value < 0) throw std::invalid_argument("negative in sqrt");
    Stack_digits.push(std::sqrt(value));
  }
  if (Stack_operators.top().operation == UnarnMinus)
    Stack_digits.push(value * (-1));
  Stack_operators.pop();
}

void Model::Calculate(std::stack<double>& Stack_digits,
                      std::stack<Leksema>& Stack_operators) {
  if (IsUnarnOrBinarn(Stack_operators.top().operation) == 2)
    CalculateBinarn(Stack_digits, Stack_operators);
  else if (IsUnarnOrBinarn(Stack_operators.top().operation) == 1)
    CalculateUnarn(Stack_digits, Stack_operators);
}
//
short Model::AddOperators(std::string expression, short index,
                          std::stack<double>& Stack_digits,
                          std::stack<Leksema>& Stack_operators) {
  if (Stack_operators.empty()) {
    Stack_operators.push(AddElement(expression, index));
  } else if (expression[index] == ')') {
    if (Stack_operators.top().operation == OpenBracket) {
      Stack_operators.pop();
    } else if (Stack_operators.top().operation != OpenBracket) {
      while (Stack_operators.top().operation != OpenBracket)
        Calculate(Stack_digits, Stack_operators);
      Stack_operators.pop();
    }
  } else if (!Stack_operators.empty() &&
             get_priority(expression, index) <=
                 Stack_operators.top().priority &&
             expression[index] != '(') {
    Calculate(Stack_digits, Stack_operators);
    AddOperators(expression, index, Stack_digits, Stack_operators);
  } else if ((!Stack_operators.empty() && get_priority(expression, index) >
                                              Stack_operators.top().priority) ||
             expression[index] == '(') {
    Stack_operators.push(AddElement(expression, index));
  }
  return get_length(get_enum_type(expression, index));
}

short Model::AddDigits(std::string expression, short index,
                       std::stack<double>& Stack_digits) {
  short start = index;
  double res = 0;

  while (isdigit(expression[index]) || expression[index] == '.') index++;
  res = std::stod(expression.substr(start, index));
  if ((expression[start - 1] == '+' || expression[start - 1] == '-') &&
      expression[start - 2] == 'E')
    Stack_digits.push(Stack_digits.top() * std::pow(10, res));
  else
    Stack_digits.push(res);
  index--;
  return index - start;
}

double Model::CalculateResult(std::stack<double>& Stack_digits,
                              std::stack<Leksema>& Stack_operators) {
  while (!Stack_operators.empty()) Calculate(Stack_digits, Stack_operators);
  return Stack_digits.top();
}

bool Model::IsCorrectBrackets(std::string expression) {
  short counter = 0;
  bool res = true;

  for (size_t i = 0; i < expression.length(); i++) {
    if (expression[i] == '(') counter++;
    if (expression[i] == ')') counter--;
    if (counter < 0) res = false;
    ;
  }
  if (counter != 0) res = false;
  return res;
}

bool Model::IsCorrectExpression(std::string expression) {
  bool is_ok = true;
  short len = expression.length() - 1;

  if (len > 255 || !IsCorrectBrackets(expression)) is_ok = false;
  if (!isdigit(expression[len]) && expression[len] != ')') is_ok = false;
  return is_ok;
}

double Model::Processing(std::string expression, double x) {
  std::stack<double> Stack_digits;
  std::stack<Leksema> Stack_operators;

  if (expression == "") return 0;
  for (size_t index = 0; index < expression.length(); index++) {
    if (expression[index] == '-' && expression[index - 1] == '(')
      expression[index] = '~';
    if (expression[index] >= '0' && expression[index] <= '9')
      index += AddDigits(expression, index, Stack_digits);
    else if (expression[index] == 'x')
      Stack_digits.push(x);
    else if (expression[index] == 'E')
      index++;
    else
      index +=
          AddOperators(expression, index, Stack_digits, Stack_operators) - 1;
  }
  return CalculateResult(Stack_digits, Stack_operators);
}

std::vector<double> Model::GetXCoordinate(double xmin, double xmax) {
  std::vector<double> x;
  double step = 0.001 * (fabs(xmin) + fabs(xmax));
  double X = xmin;

  while (X < xmax) {
    x.push_back(X);
    X += step;
  }
  return x;
}

std::vector<double> Model::GetYCoordinate(std::string str, double xmin,
                                          double xmax) {
  std::vector<double> y;
  double step = 0.001 * (fabs(xmin) + fabs(xmax));
  double Y = 0;
  double X = xmin;

  while (X < xmax) {
    Y = Processing(str, X);
    y.push_back(Y);
    X += step;
  }
  return y;
}
