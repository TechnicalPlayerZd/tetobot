#include "main.h"

// === Device Setup ===
pros::Motor motor19(19, pros::E_MOTOR_GEARSET_18, false);
pros::Motor motor18(18, pros::E_MOTOR_GEARSET_18, false);
pros::Motor motor20(20, pros::E_MOTOR_GEARSET_18, false);

pros::Controller master(pros::E_CONTROLLER_MASTER);

// Pneumatic solenoid on 3-wire port A
pros::ADIDigitalOut solenoid('A');

// === MAIN CONTROL LOOP ===
int main() {
  // Set initial motor config
  motor19.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  motor18.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  motor20.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

  bool solenoidState = false; // start retracted

  while (true) {
    // === Motor Control ===
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      // All motors spin forward
      motor19.move_velocity(120); // 60% * 200 rpm
      motor18.move_velocity(120);
      motor20.move_velocity(120);
    } 
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      // One motor reverses
      motor19.move_velocity(120);
      motor20.move_velocity(-120);
      motor18.move_velocity(120);
    } 
    else {
      // Stop motors
      motor19.move_velocity(0);
      motor18.move_velocity(0);
      motor20.move_velocity(0);
    }

    // === Pneumatics Toggle ===
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      solenoidState = !solenoidState;       // toggle
      solenoid.set_value(solenoidState);
    }

    // Optional: force retract with L2
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      solenoidState = false;
      solenoid.set_value(false);
    }

    // Small delay for stability
    pros::delay(10);
  }
}
