#include "modes/Secret.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

Secret::Secret(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::mod_x  },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right},
        socd::SocdPair{ &InputState::c_down, &InputState::c_up   },
    };
}

void Secret::HandleSocd(InputState &inputs) {
    // Up > Down
    if (inputs.down && inputs.mod_x) {
        inputs.down = false;
    }
    InputMode::HandleSocd(inputs);
}

void Secret::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    // AttackLeft
    outputs.x = inputs.b;
    // AttackRight
    outputs.b = inputs.z;
    // AttackDown
    outputs.a = inputs.x;
    // AttackUp
    outputs.y = inputs.a;

    // Boost
    outputs.triggerLDigital = inputs.l || inputs.up;

    // Pause
    outputs.start = inputs.start;

    if (inputs.mod_y) {
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
        outputs.dpadDown = inputs.c_down;
        outputs.dpadUp = inputs.c_up;
    }

    // DebugPause
    outputs.select = inputs.midshield;
    // DebugModifier
    outputs.buttonL = inputs.mod_y;
    // DebugFrameStep
    outputs.triggerRDigital = inputs.y;
}

void Secret::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.mod_x,
        inputs.c_left && !inputs.mod_y,
        inputs.c_right && !inputs.mod_y,
        inputs.c_down && !inputs.mod_y,
        inputs.c_up && !inputs.mod_y,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
}
