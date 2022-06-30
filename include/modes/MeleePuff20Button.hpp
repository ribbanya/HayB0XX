#ifndef _MODES_MELEEPUFF20BUTTON_HPP
#define _MODES_MELEEPUFF20BUTTON_HPP

#include "modes/Melee20Button.hpp"
#include "core/socd.hpp"

class MeleePuff20Button : public Melee20Button {
  public:
    MeleePuff20Button(socd::SocdType socd_type);

  protected:
    virtual void RemapInputs(InputState &inputs);
};

#endif
