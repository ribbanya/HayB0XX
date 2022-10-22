#include "modes/MeleeYoshi20Button.hpp"

MeleeYoshi20Button::MeleeYoshi20Button(socd::SocdType socd_type) : Melee20Button(socd_type) {
    // Shallowest 1f airdodge from frame 2 of full hop: 8625 4625 = 28.20°
    wavedash_angle_mx = { .x = 69, .y = 37 };

    // Shallowest 0f airdodge from frame 2 of full hop: 4375 8875 = 52.06°
    wavedash_angle_my = { .x = 35, .y = 71};
}

void MeleeYoshi20Button::RemapInputs(InputState &inputs) {
    InputState old = inputs;
    inputs.up = old.b;
    inputs.c_down = old.up;
    inputs.b = old.c_down;
}