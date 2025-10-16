/**
 * @file driver.hpp
 * @brief Driver control subsystem for teleoperated operation.
 * @author Lena
 * 
 * This header declares the Driver subsystem, which reads input from the
 * primary controller and translates it into drivetrain commands. It runs
 * in its own task and periodically polls the controller state to update
 * the robot's movement.
 */
#pragma once

#include "subsystem.hpp"

namespace subsystem {

/**
 * @brief Driver control subsystem for teleoperated operation.
 *
 * This subsystem reads input from the primary controller and translates
 * it into drivetrain commands. It runs in its own task and periodically
 * polls the controller state to update the robot's movement.
 */
class Driver final : public subsystem::Subsystem {
  public:
    Driver() : Subsystem("Driver") {}
  protected:
    void tick() override;
    void on_enable() override;
    void on_disable() override;
};
}