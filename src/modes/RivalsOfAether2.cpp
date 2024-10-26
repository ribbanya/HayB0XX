#include "modes/RivalsOfAether2.hpp"

#include <cstdint>

#define ANALOG_STICK_MIN 20
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MAX 236

RivalsOfAether2::RivalsOfAether2(socd::SocdType lstick_socd_type, socd::SocdType rstick_socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right,   lstick_socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::l,       lstick_socd_type },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, rstick_socd_type },
        socd::SocdPair{ &InputState::up,     &InputState::c_up,    rstick_socd_type },
    };
}

void RivalsOfAether2::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.buttonL = inputs.lightshield;
    outputs.buttonR = inputs.midshield;
    outputs.rightStickClick = inputs.z;
    outputs.triggerRDigital = inputs.a;
    outputs.triggerLDigital = inputs.c_down;

    // Activate D-Pad layer by holding Mod X + Mod Y.
    if (inputs.mod_x && inputs.mod_y) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.up;
        outputs.dpadLeft = inputs.c_left;
        outputs.dpadRight = inputs.c_right;
    }

    if (inputs.mod_x && !inputs.mod_y) {
        outputs.select = inputs.start;
    } else if (inputs.mod_y && !inputs.mod_x) {
        outputs.home = inputs.start;
    } else {
        outputs.start = inputs.start;
    }
}

void RivalsOfAether2::UpdateAnalogOutputs(InputState &inputs, OutputState &outputs) {
    // Coordinate calculations to make modifier handling simpler.
    UpdateDirections(
        inputs.left,
        inputs.right,
        inputs.down,
        inputs.l,
        inputs.c_left,
        inputs.c_right,
        inputs.up,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.l || inputs.r;

    // 48 total DI angles, 24 total Up b angles, 16 total airdodge angles

    if (inputs.mod_x) {
        if (directions.horizontal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 66);
            // MX Horizontal Tilts
            if (inputs.a) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 44);
            }
        }

        if (directions.vertical) {
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 44);
            // MX Vertical Tilts
            if (inputs.a) {
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 67);
            }
        }

        /* Extra DI, Air Dodge, and Up B angles */
        if (directions.diagonal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 59);
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 23);

            // Angles just for DI and Up B
            if (inputs.up) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 49);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 24);
            }

            // Angles just for DI
            if (inputs.c_left) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 52);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 31);
            }

            if (inputs.c_up) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 49);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 35);
            }

            if (inputs.c_right) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 51);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 43);
            }
        }
    }

    if (inputs.mod_y) {
        if (directions.horizontal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 44);
        }

        if (directions.vertical) {
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 67);
        }

        /* Extra DI, Air Dodge, and Up B angles */
        if (directions.diagonal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 44);
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 113);

            // Angles just for DI and Up B
            if (inputs.up) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 44);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 90);
            }

            // Angles just for DI
            if (inputs.c_left) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 44);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 74);
            }

            if (inputs.c_up) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 45);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 63);
            }

            if (inputs.c_right) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 47);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 57);
            }
        }
    }

    if (directions.x < 0) {
        --outputs.leftStickX;
    }

    if (directions.y < 0) {
        --outputs.leftStickY;
    }

    // Shut off C-stick when using D-Pad layer.
    if (inputs.mod_x && inputs.mod_y) {
        outputs.rightStickX = ANALOG_STICK_NEUTRAL;
        outputs.rightStickY = ANALOG_STICK_NEUTRAL;
    }

    // Nunchuk overrides left stick.
    if (inputs.nunchuk_connected) {
        outputs.leftStickX = inputs.nunchuk_x;
        outputs.leftStickY = inputs.nunchuk_y;
    }
}
