#ifndef _MODES_RABBITANDSTEEL_HPP
#define _MODES_RABBITANDSTEEL_HPP

#include "core/KeyboardMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class RabbitAndSteel : public KeyboardMode {
  public:
    RabbitAndSteel();

  private:
    void UpdateKeys(InputState &inputs);
};

#endif
