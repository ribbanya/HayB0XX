#include "modes/GgstMode.hpp"

#include "core/socd.hpp"

#define ANALOG_STICK_MIN 0
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

GgstMode::GgstMode() {
    _socd_pair_count = 2;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,  &InputState::right},
        socd::SocdPair{ &InputState::down, &InputState::mod_x},
    };
}

void GgstMode::HandleSocd(InputState &inputs) {
    InputMode::HandleSocd(inputs);
}

void GgstMode::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Menu keys
    outputs.start = inputs.start;
    outputs.home = inputs.c_down;
    outputs.select = inputs.mod_y;

    // Thumb buttons
    outputs.dpadUp = inputs.mod_x;
    outputs.triggerLDigital = inputs.c_up;
    outputs.triggerRDigital = inputs.c_right;

    // Left hand
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    outputs.leftStickClick = inputs.l;

    // Right hand bottom row
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.buttonL = inputs.z;
    outputs.buttonR = inputs.up;

    // Right hand top row
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.rightStickClick = inputs.lightshield;
}

void GgstMode::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = ANALOG_STICK_NEUTRAL;
    outputs.leftStickY = ANALOG_STICK_NEUTRAL;
    outputs.rightStickX = ANALOG_STICK_NEUTRAL;
    outputs.rightStickY = ANALOG_STICK_NEUTRAL;
    outputs.triggerLAnalog = outputs.triggerLDigital ? 255 : 0;
    outputs.triggerRAnalog = outputs.triggerRDigital ? 255 : 0;
}
