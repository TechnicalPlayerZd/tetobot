/**
 * @file subsystem.hpp
 * @brief Base class for lightweight, periodic subsystems backed by a PROS task.
 * @author Lena
 * 
 * This header documents subsystem::Subsystem, a minimal, reusable base class that
 * encapsulates the common pattern of running periodic work inside a dedicated task.
 * Subsystems derived from this class run a virtual tick() method repeatedly at an
 * interval returned by get_delay(), and expose simple lifecycle control via enable()
 * and disable().
 */

#pragma once

#include "api.h"

/**
 * @namespace subsystem
 * @brief Encapsulates the base Subsystem class and related functionality.
 *
 * This namespace contains various classes and functions related to robot
 * subsystems, including the Subsystem base class, which provides a framework
 * for creating modular robot subsystems that run in their own tasks. It includes
 * methods for enabling/disabling the subsystem and virtual hooks for custom
 * behavior.
 */
namespace subsystem {
class Subsystem {
  public:
    Subsystem(std::string name = "") : name(name) {};
    virtual ~Subsystem() = default;

    /**
     * @brief Enable the subsystem by creating and starting its associated task.
     *
     * If the subsystem is already enabled (i.e., has a non-null task pointer),
     * this function does nothing. Otherwise, it creates a new task that runs
     * the subsystem's `tick()` method at regular intervals defined by
     * `get_delay()`. The task runs indefinitely until the subsystem is disabled.
     */
    void enable();
    /**
     * @brief Disable the subsystem by terminating its associated task.
     *
     * If the subsystem is not currently enabled (i.e., has a null task pointer),
     * this function does nothing. Otherwise, it deletes the existing task,
     * sets the task pointer to null, and calls the `on_disable()` hook for
     * any necessary cleanup.
     */
    void disable();
    /**
     * @brief Determine whether the subsystem is enabled.
     *
     * A subsystem is considered enabled when it has an associated task (i.e., the internal
     * task pointer is non-null). This is a non-mutating check.
     *
     * @return true if the subsystem has an assigned task and is therefore enabled; false otherwise.
     */
    bool is_enabled() const { return task != nullptr; }

  protected:
    /**
     * @brief Human-readable, immutable name of the subsystem.
     *
     * Used as an identifier for logging, diagnostics and user interfaces.
     * Stored as a std::string and declared const to prevent modification after construction.
     */
    const std::string name;
    /**
     * @brief Pointer to the task associated with this subsystem.
     *
     * This task is responsible for running the subsystem's main loop at the
     * specified interval. It is created when the subsystem is enabled and
     * destroyed when the subsystem is disabled.
     */
    pros::task_t task = nullptr;

    /**
     * @brief Get the delay interval (in seconds) between successive calls to `tick()`.
     *
     * This function returns the time interval that the subsystem's task should
     * wait between successive invocations of the `tick()` method. The default
     * implementation returns 0.01 seconds (10 milliseconds), but derived classes
     * can override this method to specify a different interval as needed.
     *
     * @return The delay interval in seconds.
     */
    virtual const float get_delay() const { return 0.01; }

    /**
     * @brief Main periodic function that runs in the subsystem's task.
     *
     * This virtual method is called repeatedly at intervals defined by
     * `get_delay()` when the subsystem is enabled. Derived classes should
     * override this method to implement the subsystem's periodic behavior.
     * The default implementation does nothing.
     */
    virtual void tick() {};

    /**
     * @brief Hook called once when the subsystem is enabled.
     *
     * This virtual method is invoked once when the subsystem is enabled,
     * before the first call to `tick()`. Derived classes can override this
     * method to perform any necessary initialization or setup. The default
     * implementation does nothing.
     */
    virtual void on_enable() {};

    /**
     * @brief Hook called once when the subsystem is disabled.
     *
     * This virtual method is invoked once when the subsystem is disabled,
     * after the task has been deleted. Derived classes can override this
     * method to perform any necessary cleanup or teardown. The default
     * implementation does nothing.
     */
    virtual void on_disable() {};
};

/**
 * @brief Initialize all robot subsystems.
 */
void init();
}