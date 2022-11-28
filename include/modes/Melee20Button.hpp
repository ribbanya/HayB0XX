#ifndef _MODES_MELEE20BUTTON_HPP
#define _MODES_MELEE20BUTTON_HPP

#include "core/ControllerMode.hpp"
#include "core/socd.hpp"
#include "core/state.hpp"

typedef struct {
    bool crouch_walk_os = false;
} Melee20ButtonOptions;

class Melee20Button : public ControllerMode {
  public:
    Melee20Button(socd::SocdType socd_type);

  protected:
    void UpdateDigitalOutputs(InputState &inputs, OutputState &outputs);
    void UpdateAnalogOutputs(InputState &inputs, OutputState &outputs);

    OutputAngle wavedash_angle_mx;
    OutputAngle wavedash_angle_my;

  private:
    Melee20ButtonOptions _options;
    bool _horizontal_socd;

    void HandleSocd(InputState &inputs);
};

#endif
