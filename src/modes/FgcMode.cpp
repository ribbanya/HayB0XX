#define ANALOG_STICK_MIN 0
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 255

#include "modes/FgcMode.hpp"

FgcMode::FgcMode(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 1;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left, &InputState::right},
    };
}

void FgcMode::HandleSocd(InputState &inputs) {
    if (inputs.down && (inputs.mod_x || inputs.a)) {
        inputs.down = false;
    }
    InputMode::HandleSocd(inputs);
}

void FgcMode::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // Directions
    outputs.dpadLeft = inputs.left;
    outputs.dpadRight = inputs.right;
    outputs.dpadDown = inputs.down;
    outputs.dpadUp = inputs.mod_x || inputs.a;

    // Menu keys
    outputs.start = inputs.start;
    outputs.select = inputs.c_left;
    outputs.home = inputs.c_right;

    // Stick clicks
    outputs.leftStickClick = inputs.l;
    outputs.rightStickClick = inputs.c_up;

    // Right hand bottom row
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.buttonL = inputs.z;
    outputs.buttonR = inputs.up;

    // Right hand top row
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.triggerLDigital = inputs.lightshield;
    outputs.triggerRDigital = inputs.midshield;
}

void FgcMode::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    outputs.leftStickX = ANALOG_STICK_NEUTRAL;
    outputs.leftStickY = ANALOG_STICK_NEUTRAL;
    outputs.rightStickX = ANALOG_STICK_NEUTRAL;
    outputs.rightStickY = ANALOG_STICK_NEUTRAL;
    outputs.triggerLAnalog = outputs.triggerLDigital ? 255 : 0;
    outputs.triggerRAnalog = outputs.triggerRDigital ? 255 : 0;
}
