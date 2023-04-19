#include "modes/Secret.hpp"

#define ANALOG_STICK_MIN 28
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 228

Secret::Secret(socd::SocdType socd_type) : ControllerMode(socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{&InputState::left,    &InputState::right  },
        socd::SocdPair{ &InputState::down,   &InputState::up     },
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
    outputs.triggerLDigital = inputs.l;
    // Pause
    outputs.start = inputs.start;

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
        inputs.c_left,
        inputs.c_right,
        inputs.c_down,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );
}
