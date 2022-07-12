#ifndef _MODES_MELEE20BUTTON_HPP
#define _MODES_MELEE20BUTTON_HPP

#include "core/socd.hpp"
#include "core/state.hpp"
#include "modes/PlatformFighter.hpp"

typedef struct melee_coords {
    uint8_t trigger_light;
    uint8_t trigger_mid;
    uint8_t trigger_hard;

    uint16_t horizontal_ledgedash;
    uint16_t horizontal_b_my;

    OutputCoords origin;

    OutputCoords axis;
    OutputCoords axis_mx;
    OutputCoords axis_my;

    OutputCoords quadrant;
    OutputCoords quadrant_mx;
    OutputCoords quadrant_my;

    OutputCoords airdodge_quadrant12;
    OutputCoords airdodge_quadrant34;
    OutputCoords airdodge_quadrant12_mx;
    OutputCoords airdodge_quadrant34_mx;
    OutputCoords airdodge_quadrant12_my;
    OutputCoords airdodge_quadrant34_my;

    OutputCoords quadrant_mx_cd;
    OutputCoords quadrant_mx_cl;
    OutputCoords quadrant_mx_cu;
    OutputCoords quadrant_mx_cr;

    OutputCoords quadrant_my_cr;
    OutputCoords quadrant_my_cu;
    OutputCoords quadrant_my_cl;
    OutputCoords quadrant_my_cd;

    OutputCoords quadrant_b_mx;
    OutputCoords quadrant_b_mx_cd;
    OutputCoords quadrant_b_mx_cl;
    OutputCoords quadrant_b_mx_cu;
    OutputCoords quadrant_b_mx_cr;

    OutputCoords quadrant_b_my;
    OutputCoords quadrant_b_my_cr;
    OutputCoords quadrant_b_my_cu;
    OutputCoords quadrant_b_my_cl;
    OutputCoords quadrant_b_my_cd;

    OutputCoords c_origin;
    OutputCoords c_quadrant;
    OutputCoords c_fsmash;
} MeleeCoords;

class Melee20Button : public PlatformFighter {
  public:
    Melee20Button(socd::SocdType socd_type);

  private:
    virtual void UpdateDigitalOutputs();
    virtual void UpdateAnalogOutputs();
};

#endif
