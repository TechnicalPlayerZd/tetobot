/**
 * @file include/keybinds.hpp
 * @brief Centralized key-bind definitions for controller input.
 * @author Lena
 *
 * This header groups type aliases and predefined key bindings used to
 * represent controller buttons in the project. Keeping bindings in one
 * place simplifies remapping and improves readability.
 */

#pragma once

#include "pros/misc.h"

/**
 * @namespace keybinds
 * @brief Encapsulates controller key types and predefined bindings.
 *
 * All key-related types and constants live in this namespace to avoid
 * polluting the global scope and to make intent explicit at the call site.
 */
namespace keybinds {
/**
 * @brief Alias for the integral type representing controller keys.
 *
 * Use keybinds::key_t when declaring variables or parameters that hold
 * controller key codes. Defining a single alias makes it trivial to
 * change the underlying representation later (for example, switching to
 * a strongly typed enum) without modifying call sites.
 */
using key_t = int;

/**
 * @brief Example controller binding for the "A" digital button.
 *
 * Provides a ready-to-use key value corresponding to the controller's
 * "A" button as defined by the PROS API. This constant serves as an
 * example or default binding; replace or extend it with project-specific
 * bindings as needed.
 */
inline constexpr key_t EXAMPLE_BIND = pros::E_CONTROLLER_DIGITAL_A;
}