#include "modes/RivalsOfAether2.hpp"

#include <cstdint>

#define ANALOG_STICK_MAG 127
#define ANALOG_STICK_NEUTRAL 128
#define ANALOG_STICK_MIN (ANALOG_STICK_NEUTRAL - ANALOG_STICK_MAG)
#define ANALOG_STICK_MAX (ANALOG_STICK_NEUTRAL + ANALOG_STICK_MAG)

#define TILT_MIN 51
#define WALK_MIN 51
#define WALK_MAX 94
#define CROUCH_MIN 80

RivalsOfAether2::RivalsOfAether2(socd::SocdType lstick_socd_type, socd::SocdType rstick_socd_type) {
    _socd_pair_count = 4;
    _socd_pairs = new socd::SocdPair[_socd_pair_count]{
        socd::SocdPair{ &InputState::left,   &InputState::right,   lstick_socd_type },
        socd::SocdPair{ &InputState::down,   &InputState::l,       lstick_socd_type },
        socd::SocdPair{ &InputState::c_left, &InputState::c_right, rstick_socd_type },
        socd::SocdPair{ &InputState::z,      &InputState::c_up,    rstick_socd_type },
    };
}

void RivalsOfAether2::UpdateDigitalOutputs(InputState &inputs, OutputState &outputs) {
    outputs.a = inputs.b;
    outputs.b = inputs.x;
    outputs.x = inputs.r;
    outputs.y = inputs.y;
    outputs.buttonL = inputs.lightshield;
    outputs.buttonR = inputs.midshield;
    outputs.rightStickClick = inputs.up;
    outputs.triggerRDigital = inputs.a;
    outputs.triggerLDigital = inputs.c_down;

    // Activate D-Pad layer by holding Mod X + Mod Y.
    if (inputs.mod_x && inputs.mod_y) {
        outputs.dpadUp = inputs.c_up;
        outputs.dpadDown = inputs.z;
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
        inputs.z,
        inputs.c_up,
        ANALOG_STICK_MIN,
        ANALOG_STICK_NEUTRAL,
        ANALOG_STICK_MAX,
        outputs
    );

    bool shield_button_pressed = inputs.l || inputs.r;

    if (directions.diagonal) {
        outputs.leftStickX = ANALOG_STICK_NEUTRAL + directions.x * 90;
        outputs.leftStickY = ANALOG_STICK_NEUTRAL + directions.y * 90;
        // 34 = 0.000
        // 35 = 0.006
        // 36 = 0.019
        // 39 = 0.058
        // 40 = 0.071
        // 63 = 0.372
        // 94 = 0.777
        // 126 = 1.000
        // 127 = 1.000
    }

    // 48 total DI angles, 24 total Up b angles, 16 total airdodge angles

    if (inputs.mod_x) {
        if (directions.horizontal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + directions.x * WALK_MAX;
            // MX Horizontal Tilts
            if (inputs.a) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * TILT_MIN);
            }
        }

        if (directions.vertical) {
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + directions.y * 64;
            // MX Vertical Tilts
            if (inputs.a) {
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * TILT_MIN);
            }
        }

        /* Extra DI, Air Dodge, and Up B angles */
        if (directions.diagonal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 113);
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 44);

            // Angles just for DI and Up B
            if (inputs.z) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 90);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 44);
            }

            // Angles just for DI
            if (inputs.c_left) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 74);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 44);
            }

            if (inputs.c_up) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 63);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 45);
            }

            if (inputs.c_right) {
                outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 57);
                outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 47);
            }
        }
    }

    if (inputs.mod_y) {
        if (directions.horizontal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * WALK_MIN);
        }

        if (directions.vertical) {
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * CROUCH_MIN);
        }

        /* Extra DI, Air Dodge, and Up B angles */
        if (directions.diagonal) {
            outputs.leftStickX = ANALOG_STICK_NEUTRAL + (directions.x * 44);
            outputs.leftStickY = ANALOG_STICK_NEUTRAL + (directions.y * 113);

            // Angles just for DI and Up B
            if (inputs.z) {
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
