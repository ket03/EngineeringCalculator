#ifndef COTROLLER_H
#define COTROLLER_H

#include "../Model/model.h"

class Controller {
 public:
  Controller() {}
  ~Controller() {}
  double Calculate(std::string str, double x);
  bool Validate(std::string str);
  std::vector<double> GetCoordinateX(double xmin, double xmax);
  std::vector<double> GetCoordinateY(std::string str, double xmin, double xmax);

 private:
  Model model_;
};

#endif  // COTROLLER_H
