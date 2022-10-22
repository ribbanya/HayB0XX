#include "modes/MeleePuff20Button.hpp"

MeleePuff20Button::MeleePuff20Button(socd::SocdType socd_type) : Melee20Button(socd_type) {
    // SWT minimum angle: 9125 3875 = 73 31 = 23.01°
    wavedash_angle_mx = { .x = 73, .y = 31 };

    // Shallowest 0f airdodge from frame 2 of full hop: 7500 5250 = 57 40 = 35.06°
    wavedash_angle_my = { .x = 57, .y = 40};
}

void MeleePuff20Button::RemapInputs(InputState &inputs) {
    InputState old = inputs;
    inputs.up = old.b;
    inputs.b = old.up;
}