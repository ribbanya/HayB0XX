#include "modes/MeleePuff20Button.hpp"

MeleePuff20Button::MeleePuff20Button(socd::SocdType socd_type) : Melee20Button(socd_type) {
    // SWT: 9125 3875 = 73 31 = 23.01°
    wavedash_angle = { .x = 73, .y = 31 };
}

void MeleePuff20Button::RemapInputs(InputState &inputs) {
    InputState old = inputs;
    inputs.up = old.b;
    inputs.b = old.up;
}