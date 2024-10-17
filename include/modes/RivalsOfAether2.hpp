#ifndef _MODES_RIVALSOFAETHER2_HPP
#define _MODES_RIVALSOFAETHER2_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class RivalsOfAether2 : public ControllerMode {
  public:
    RivalsOfAether2(socd::SocdType socd_type);

  private:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
