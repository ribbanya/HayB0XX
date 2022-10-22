#ifndef _MODES_MELEEYOSHI20BUTTON_HPP
#define _MODES_MELEEYOSHI20BUTTON_HPP

#include "modes/Melee20Button.hpp"
#include "core/socd.hpp"

class MeleeYoshi20Button : public Melee20Button {
  public:
    MeleeYoshi20Button(socd::SocdType socd_type);

  protected:
    virtual void RemapInputs(InputState &inputs);
};

#endif
