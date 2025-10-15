#pragma once

#include "api.h"

namespace subsystem {
class Subsystem {
  public:
    Subsystem(std::string name = "") : name(name) {};
    virtual ~Subsystem() = default;

    void enable() {
      if (is_enabled()) return;
      task = pros::c::task_create([](void* param) {
        Subsystem* self = static_cast<Subsystem*>(param);
        self->on_enable();
        while (true) {
          self->tick();
          pros::delay(self->get_delay() * 1000);
        }
      }, this, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, name.c_str());
    }
    void disable() {
      if (!is_enabled()) return;
      pros::c::task_delete(task);
      task = nullptr;
      on_disable();
    }
    bool is_enabled() const { return task != nullptr; }

  protected:
    const std::string name;
    // Note: I fucking hate pros c++ api tasks (flashbacks)
    pros::task_t task = nullptr;

    virtual const float get_delay() const { return 0.01; }

    virtual void tick() {};
    virtual void on_enable() {};
    virtual void on_disable() {};
};

}