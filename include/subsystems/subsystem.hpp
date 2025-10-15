
#pragma once

#include "api.h"

namespace subsystem {
class Subsystem {
  public:
    Subsystem(std::string name) : name(name) {};
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
    void disable();
    bool is_enabled() const { return task != nullptr; }

  protected:
    std::string name;
    // Note: I fucking hate pros c++ tasks (flashbacks)
    pros::task_t task;

    virtual const float get_delay() const { return 0.01; }

    virtual void tick();
    virtual void on_enable();
    virtual void on_disable();
};

}