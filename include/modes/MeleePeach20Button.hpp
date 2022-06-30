#ifndef _MODES_MELEEPEACH20BUTTON_HPP
#define _MODES_MELEEPEACH20BUTTON_HPP

#include "modes/Melee20Button.hpp"
#include "core/socd.hpp"

class MeleePeach20Button : public Melee20Button {
  public:
    MeleePeach20Button(socd::SocdType socd_type);

  protected:
    virtual void RemapInputs(InputState &inputs);
};

#endif
