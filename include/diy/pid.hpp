#pragma once
#include <cmath>

class PID {
public:
  PID(double kP, double kI, double kD);

  void setTarget(double target);
  double calculate(double current);
  void reset();

private:
  double kP, kI, kD;
  double target;
  double error, prevError, integral;
};
