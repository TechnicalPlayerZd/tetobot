#include "subsystem.hpp"

namespace driver {
class Driver final : public subsystem::Subsystem {
  public:
    Driver() : Subsystem("Driver") {}
  protected:
    void tick() override;
    void on_enable() override;
    void on_disable() override;
};
}