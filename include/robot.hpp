/**
 * @file robot.hpp
 * @brief Declarations for global robot objects.
 * @author Lena
 * @date 2025-10-14
 *
 * This header declares the robot-related global objects used across the
 * project: controller, motor groups, IMU/encoder sensors, tracking wheels,
 * odometry helpers, controller tuning structures, and the high level chassis
 * object.
 */

#pragma once

#include "api.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/misc.hpp"

namespace robot {

/**
 * @brief Primary operator controller for the robot.
 *
 * This object represents the master human interface (joysticks, buttons).
 * It is intentionally non-const because it maintains runtime state such as
 * button information and joystick state.
 *
 * Usage: read joystick axes and button states from this object in
 * operator-control code. The controller instance is created/initialized in
 * the chassis implementation file.
 */
extern pros::Controller master;

/**
 * @brief Left and right motor groups for the drivetrain.
 *
 * These group together the physical motors on each side of the robot and
 * provide a convenient API for setting speeds or settings. They are
 * declared non-const to reflect their mutable runtime behaviour (e.g. motor
 * brake modes, enable/disable).
 */
extern pros::MotorGroup left, right;

/**
 * @brief High-level drivetrain helper from LemLib.
 *
 * This object wraps the left/right motor groups and provides constants
 * associated with the drivetrain (wheel size, track width).
 */
extern lemlib::Drivetrain drivetrain;

/**
 * @brief Inertial Measurement Unit (IMU) used for heading and angular
 *        acceleration/rotation measurements.
 *
 * Typically used for angle estimation and closed-loop angular control.
 */
extern pros::IMU imu;

/**
 * @brief Rotation sensor used as a vertical tracking encoder.
 *
 * Represents an encoder used by the odometry system; naming convention
 * follows the odom/tracking-wheel layout (vertical = along robot forward
 * axis). The specific port and initialization are done in the source file.
 */
extern pros::Rotation vertical_encoder;

/**
 * @brief Rotation sensor used as a lateral tracking encoder.
 *
 * Represents an encoder orthogonal to the vertical encoder used to measure
 * lateral displacement for odometry.
 */
extern pros::Rotation lateral_encoder;

/**
 * @brief Tracking wheel abstraction (vertical).
 *
 * A LemLib helper that adapts a physical encoder/rotation sensor to the
 * tracking-wheel interface expected by the odometry routines.
 */
extern lemlib::TrackingWheel vertical_wheel;

/**
 * @brief Tracking wheel abstraction (lateral).
 *
 * See `vertical_wheel` for details.
 */
extern lemlib::TrackingWheel lateral_wheel;

/**
 * @brief Odometry sensor bundle combining the available tracking sensors.
 *
 * Contains the set of tracking wheels/encoders required by LemLib's
 * odometry implementation to compute the robot pose (x, y, theta).
 */
extern lemlib::OdomSensors odom;

/**
 * @brief Controller settings for the translational (vertical) controller.
 *
 * Stores PID, anti-windup, error & timeout ranges, and motion constraints
 * used by the vertical motion controller. Tuning values are
 * provided/initialized in the implementation file.
 */
extern lemlib::ControllerSettings vertical_controller;

/**
 * @brief Controller settings for the angular (heading) controller.
 *
 * Stores PID, anti-windup, error & timeout ranges, and motion constraints
 * used by the angular/heading controller.
 */
extern lemlib::ControllerSettings angular_controller;


/**
 * @brief Exponential throttle response curve for drive control.
 *
 * A globally declared lemlib::ExpoDriveCurve instance that maps raw throttle or joystick
 * input into motor command output using an exponential response. The curve provides
 * increased resolution and smoother control around the center (low inputs) while still
 * allowing full power at the extremes.
 *
 * See also: implementation file for exact parameter defaults and any convenience methods
 * provided by lemlib::ExpoDriveCurve to compute output from input values.
 */
extern lemlib::ExpoDriveCurve throttle_curve, steer_curve;

/**
 * @brief High-level chassis object that exposes drive/trajectory APIs.
 *
 * This is the primary interface used by autonomous and operator code to
 * command the robot's motion (move distance, turn to angle, follow paths,
 * etc.). It composes the drivetrain, odometry, and controller settings.
 */
extern lemlib::Chassis chassis;

/**
 * @brief Initialize all chassis-related hardware and software objects.
 *
 * This function performs any required initialization such as:
 *  - configuring and resetting sensors (IMU, encoders)
 *  - constructing/attaching tracking wheels to encoders
 *  - configuring motor groups and drivetrain parameters
 *  - initializing odometry structures and controller tuning values
 *
 * Call this early in program startup (for example from `initialize()` in
 * `src/main.cpp`) before using any other symbols in this namespace.
 */
void init();

}
