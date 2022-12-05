#ifndef _MODES_MELEEMARTH20BUTTON_HPP
#define _MODES_MELEEMARTH20BUTTON_HPP

#include "modes/Melee20Button.hpp"
#include "core/socd.hpp"

class MeleeMarth20Button : public Melee20Button {
  public:
    MeleeMarth20Button(socd::SocdType socd_type);

  protected:
    virtual void RemapInputs(InputState &inputs);
};

#endif
