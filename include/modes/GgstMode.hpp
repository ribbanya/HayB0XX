#ifndef _MODES_GGSTMODE_HPP
#define _MODES_GGSTMODE_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

class GgstMode : public ControllerMode {
  public:
    GgstMode();

  private:
    void HandleSocd(InputState &inputs);
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);
};

#endif
