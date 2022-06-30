#include "modes/MeleePeach20Button.hpp"

MeleePeach20Button::MeleePeach20Button(socd::SocdType socd_type) : Melee20Button(socd_type) {
    // Optimal Peach: 
    wavedash_angle = { .x = 70, .y = 32 };
}

void MeleePeach20Button::RemapInputs(InputState &inputs) {
    InputState old = inputs;
    inputs.up = old.b;
    inputs.c_down = old.up;
    inputs.b = old.c_down;
}