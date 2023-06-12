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
    outputs.home = inputs.c_down;
    outputs.leftStickClick = inputs.c_up;
    outputs.rightStickClick = inputs.c_right;

    // Right hand bottom row
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.triggerLDigital = inputs.z;
    outputs.triggerRDigital = inputs.up;

    // Right hand top row
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.buttonR = inputs.midshield;
    outputs.buttonL = inputs.lightshield;
}

void FgcMode::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.mod_x || inputs.a,
        false,
        false,
        false,
        false,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
}
