#ifndef MODEL_H
#define MODEL_H

#include <stack>
#include <string>
#include <vector>

class Model {
 public:
  Model() {}
  ~Model() {}
  bool IsCorrectExpression(std::string expression);
  double Processing(std::string expression, double x);
  bool IsCorrectBrackets(std::string expression);
  std::vector<double> GetXCoordinate(double xmin, double xmax);
  std::vector<double> GetYCoordinate(std::string str, double xmin, double xmax);

 private:
  enum Operation {
    None,
    Add,
    Sub,
    Mult,
    Div,
    Pow,
    Mod,
    OpenBracket,
    CloseBracket,
    Ln,
    Log,
    Sin,
    Cos,
    Tan,
    Sqrt,
    Asin,
    Acos,
    Atan,
    UnarnMinus,
    Exp
  };

  struct Leksema {
    Operation operation;
    char priority;
  };

  Operation get_enum_type(std::string expression, short index);
  short get_length(Operation operation);
  short get_priority(std::string expression, short index);

  Leksema AddElement(std::string expression, short index);
  void CalculateBinarn(std::stack<double>& Stack_digits,
                       std::stack<Leksema>& Stack_operators);
  void CalculateUnarn(std::stack<double>& Stack_digits,
                      std::stack<Leksema>& Stack_operators);
  void Calculate(std::stack<double>& Stack_digits,
                 std::stack<Leksema>& Stack_operators);
  short AddOperators(std::string expression, short index,
                     std::stack<double>& Stack_digits,
                     std::stack<Leksema>& Stack_operators);
  short AddDigits(std::string expression, short index,
                  std::stack<double>& Stack_digits);
  double CalculateResult(std::stack<double>& Stack_digits,
                         std::stack<Leksema>& Stack_operators);

  short IsUnarnOrBinarn(Operation operation);
};

#endif  // MODEL_H
