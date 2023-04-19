#ifndef _MODES_SECRET_HPP
#define _MODES_SECRET_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class Secret : public ControllerMode {
  public:
    Secret(socd::SocdType socd_type);

  private:
    void HandleSocd(InputState &inputs);
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
