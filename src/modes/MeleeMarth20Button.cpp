#include "modes/MeleeMarth20Button.hpp"

MeleeMarth20Button::MeleeMarth20Button(socd::SocdType socd_type) : Melee20Button(socd_type) {
    // Shallowest 1f airdodge from frame 2 of full hop: 7875 4000 = 26.93°
    wavedash_angle_mx = { .x = 63, .y = 32 };

    // Shallowest 0f airdodge from frame 2 of full hop: 4000 6750 = 59.35°
    wavedash_angle_my = { .x = 32, .y = 54};
}

void MeleeMarth20Button::RemapInputs(InputState &inputs) {
    InputState old = inputs;
    inputs.up = old.b;
    inputs.c_down = old.up;
    inputs.b = old.c_down;
}