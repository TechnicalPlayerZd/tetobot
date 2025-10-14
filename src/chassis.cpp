#include "robot.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/abstract_motor.hpp"

#include "fmt/core.h"

// Controller setup
pros::Controller robot::master(pros::E_CONTROLLER_MASTER);

// Motor group setup
pros::MotorGroup robot::left({1, 2, 3}, 
    pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);
pros::MotorGroup robot::right({4, 5, 6}, 
    pros::v5::MotorGears::blue, pros::v5::MotorEncoderUnits::degrees);

// IMU and encoder setup
pros::IMU robot::imu(7);
pros::Rotation robot::vertical_encoder(8);
pros::Rotation robot::lateral_encoder(9);

// Odom wheel configs
lemlib::TrackingWheel robot::vertical_wheel(
    &robot::vertical_encoder, 2.75, 1.0, 1.0);
lemlib::TrackingWheel robot::lateral_wheel(
    &robot::lateral_encoder, 2.75, 1.0, 1.0);

// Odometry configuration
lemlib::OdomSensors robot::odom(
    &robot::vertical_wheel, nullptr, 
    &robot::lateral_wheel, nullptr, 
    &robot::imu);

// PID controllers
lemlib::ControllerSettings robot::vertical_controller(
    100, 0.0, 0.1,
    0.0,
    0.75, 0.5,
    1.5, 0.5,
    50
);

lemlib::ControllerSettings robot::angular_controller(
    100, 0.0, 0.1,
    0.0,
    2, 0.5,
    5, 0.5,
    50
);

lemlib::Chassis robot::chassis(
    robot::drivetrain, 
    robot::vertical_controller, 
    robot::angular_controller, 
    robot::odom);

void robot::init() {
    fmt::print("Initializing chassis...\n");
}