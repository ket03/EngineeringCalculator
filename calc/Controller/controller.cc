#include "controller.h"

bool Controller::Validate(std::string str) {
  return this->model_.IsCorrectExpression(str);
}

double Controller::Calculate(std::string str, double x) {
  return this->model_.Processing(str, x);
}

std::vector<double> Controller::GetCoordinateX(double xmin, double xmax) {
  return this->model_.GetXCoordinate(xmin, xmax);
}

std::vector<double> Controller::GetCoordinateY(std::string str, double xmin,
                                               double xmax) {
  return this->model_.GetYCoordinate(str, xmin, xmax);
}
