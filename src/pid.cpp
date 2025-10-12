#include "diy/pid.hpp"

PID::PID(double kP, double kI, double kD)
    : kP(kP), kI(kI), kD(kD), target(0), error(0), prevError(0), integral(0) {}

void PID::setTarget(double target) {
  this->target = target;
  this->integral = 0;
  this->prevError = 0;
}

double PID::calculate(double current) {
  error = target - current;
  integral += error;
  double derivative = error - prevError;
  prevError = error;

  return (kP * error) + (kI * integral) + (kD * derivative);
}

void PID::reset() { error = prevError = integral = 0; }
