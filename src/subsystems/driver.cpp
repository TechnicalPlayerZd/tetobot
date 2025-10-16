#include "driver.hpp"
#include "pros/misc.h"
#include "robot.hpp"

using namespace subsystem;

void Driver::tick() {
  int left_x = robot::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
  int left_y = robot::master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right_x = robot::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  int right_y = robot::master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

  robot::chassis.arcade(left_y, right_x);
}