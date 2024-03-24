#ifndef _MODES_GGSTKEYBOARDMODE_HPP
#define _MODES_GGSTKEYBOARDMODE_HPP

#include "core/KeyboardMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class GgstKeyboardMode : public KeyboardMode {
  public:
    GgstKeyboardMode(socd::SocdType socd_type);

  private:
    void UpdateKeys(InputState &inputs);
};

#endif
