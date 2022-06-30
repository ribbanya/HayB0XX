#include "modes/MeleePeach20Button.hpp"

MeleePeach20Button::MeleePeach20Button(socd::SocdType socd_type) : Melee20Button(socd_type) {
    // Shallowest 1f airdodge from full hop: 8750 4000 = 24.57°
    wavedash_angle_mx = { .x = 70, .y = 32 };

    // Shallowest 0f airdodge from full hop: 5750 7375 = 52.06°
    wavedash_angle_my = { .x = 46, .y = 59};
}

void MeleePeach20Button::RemapInputs(InputState &inputs) {
    InputState old = inputs;
    inputs.up = old.b;
    inputs.c_down = old.up;
    inputs.b = old.c_down;
}