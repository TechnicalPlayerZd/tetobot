#include "subsystem.hpp"
#include "driver.hpp"

using namespace subsystem;

static std::vector<Subsystem*> all_subsystems;

void Subsystem::enable() {
  if (is_enabled()) return;

  const auto run_task = [](void* param) {
    Subsystem* self = static_cast<Subsystem*>(param);
    self->on_enable();
    while (true) {
      self->tick();
      pros::delay(self->get_delay() * 1000);
    }
  };

  task = pros::c::task_create(
    run_task, 
    this, 
    TASK_PRIORITY_DEFAULT, 
    TASK_STACK_DEPTH_DEFAULT, 
    name.c_str());
}

void Subsystem::disable() {
  if (!is_enabled()) return;
  pros::c::task_delete(task);
  task = nullptr;
  on_disable();
}

void subsystem::init() {
  all_subsystems.push_back(new Driver());
}