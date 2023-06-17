#ifndef _MODES_SF6KEYBOARDMODE_HPP
#define _MODES_SF6KEYBOARDMODE_HPP

#include "core/KeyboardMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class SF6KeyboardMode : public KeyboardMode {
  public:
    SF6KeyboardMode();

  private:
    void UpdateKeys(InputState &inputs);
};

#endif
