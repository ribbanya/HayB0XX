#include "modes/Melee20Button.hpp"

Melee20Button::Melee20Button(socd::SocdType socd_type) : PlatformFighter(socd_type, 80) {}

void Melee20Button::UpdateDigitalOutputs() {
    _outputs->a = _inputs->a;
    _outputs->b = _inputs->b;
    _outputs->x = _inputs->x;
    _outputs->y = _inputs->y;
    _outputs->buttonR = _inputs->z;
    if (_inputs->nunchuk_connected) {
        _outputs->triggerLDigital = _inputs->nunchuk_z;
    } else {
        _outputs->triggerLDigital = _inputs->l;
    }
    _outputs->triggerRDigital = _inputs->r;
    _outputs->start = _inputs->start;

    // D-Pad layer can be activated by holding Mod X + Mod Y, or by holding the C
    // button on a nunchuk.
    if ((_inputs->mod_x && _inputs->mod_y) || _inputs->nunchuk_c) {
        _outputs->dpadUp = _inputs->c_up;
        _outputs->dpadDown = _inputs->c_down;
        _outputs->dpadLeft = _inputs->c_left;
        _outputs->dpadRight = _inputs->c_right;
    }

    if (_inputs->select)
        _outputs->dpadLeft = true;
    if (_inputs->home)
        _outputs->dpadRight = true;
}

const MeleeCoords melee20button_coords = {
    .trigger_light = 49,
    .trigger_mid = 94,
    .trigger_hard = 140,

    .horizontal_ledgedash = 10000,
    .horizontal_b_my = 10000,

    .origin = {0000,   0000 },

    .axis = { 10000, 10000},
    .axis_mx = { 6625,  5375 },
    .axis_my = { 3375,  7375 },

    .quadrant = { 7000,  7000 }, // 45°
    .quadrant_mx = { 7375,  3125 }, // 22.96377°
    .quadrant_my = { 3125,  7375 }, // 67.03623°

    .airdodge_quadrant12 = { 7000,  7000 }, // 45°
    .airdodge_quadrant34 = { 7000,  6875 }, // 44.48384°
    .airdodge_quadrant12_mx = { 6375,  3750 }, // 30.46554°
    .airdodge_quadrant34_mx = { 6375,  3750 }, // 30.46554°
    .airdodge_quadrant12_my = { 4750,  8750 }, // 61.50436°
    .airdodge_quadrant34_my = { 5000,  8500 }, // 59.53446°

    .quadrant_mx_cd = { 7000,  3625 }, // 27.37104°
    .quadrant_mx_cl = { 7875,  4875 }, // 31.77828°
    .quadrant_mx_cu = { 7000,  5125 }, // 36.18552°
    .quadrant_mx_cr = { 6125,  5250 }, // 40.59276°

    .quadrant_my_cr = { 6375,  7625 }, // 49.40724°
    .quadrant_my_cu = { 5125,  7000 }, // 53.81448°
    .quadrant_my_cl = { 4875,  7875 }, // 58.22172°
    .quadrant_my_cd = { 3625,  7000 }, // 62.62896°

    .quadrant_b_mx = { 9125,  3875 }, // 22.9638°
    .quadrant_b_mx_cd = { 6375,  5375 }, // 40.59276°
    .quadrant_b_mx_cl = { 7375,  5375 }, // 36.18552°
    .quadrant_b_mx_cu = { 8500,  5250 }, // 31.77828°
    .quadrant_b_mx_cr = { 8750,  4500 }, // 27.37104°

    .quadrant_b_my = { 3875,  9125 }, // 67.0362°
    .quadrant_b_my_cr = { 5875,  7125 }, // 49.40724°
    .quadrant_b_my_cu = { 5875,  8000 }, // 53.81448°
    .quadrant_b_my_cl = { 5250,  8500 }, // 58.22172°
    .quadrant_b_my_cd = { 4500,  8750 }, // 62.62896°

    .c_origin = { 0000,  0000 }, // 0°
    .c_quadrant = { 5250,  8500 }, // 58.29857°
    .c_fsmash = { 8500,  5250 }, // 31.70143°
};

void Melee20Button::UpdateAnalogOutputs() {
    const MeleeCoords &coords = melee20button_coords;
    UpdateDirections();

    bool shield_button_pressed = _inputs->l || _inputs->r || _inputs->lightshield || _inputs->midshield;
    if (directions.diagonal) {
        SetLeftStick(coords.quadrant);
        if (shield_button_pressed) {
            SetLeftStick(coords.airdodge_quadrant12);
            if (directions.y < 0) {
                SetLeftStick(coords.airdodge_quadrant34);
            }
        }
    }

    if (_inputs->mod_x) {
        if (directions.horizontal) {
            SetLeftStickX(coords.axis_mx.x);
        }
        if (directions.vertical) {
            SetLeftStickY(coords.axis_mx.y);
        }
        if (directions.diagonal) {
            SetLeftStick(coords.quadrant_mx);
            if (shield_button_pressed) {
                SetLeftStick(coords.airdodge_quadrant12_mx);
                if (directions.y < 0) {
                    SetLeftStick(coords.airdodge_quadrant34_mx);
                }
            }
        }

        if (directions.cx != 0) {
            SetAngledFSmash(coords.c_fsmash);
        }

        if (directions.diagonal && !shield_button_pressed) {
            SetLeftStick(coords.quadrant_mx);
            if (_inputs->c_down) {
                SetLeftStick(coords.quadrant_mx_cd);
            }
            if (_inputs->c_left) {
                SetLeftStick(coords.quadrant_mx_cl);
            }
            if (_inputs->c_up) {
                SetLeftStick(coords.quadrant_mx_cu);
            }
            if (_inputs->c_right) {
                SetLeftStick(coords.quadrant_mx_cr);
            }

            if (_inputs->b) {
                SetLeftStick(coords.quadrant_b_mx);
                if (_inputs->c_down) {
                    SetLeftStick(coords.quadrant_b_mx_cd);
                }
                if (_inputs->c_left) {
                    SetLeftStick(coords.quadrant_b_mx_cl);
                }
                if (_inputs->c_up) {
                    SetLeftStick(coords.quadrant_b_mx_cu);
                }
                if (_inputs->c_right) {
                    SetLeftStick(coords.quadrant_b_mx_cr);
                }
            }
        }
    }

    if (_inputs->mod_y) {
        if (directions.horizontal) {
            SetLeftStickX(coords.axis_my.x);
        }
        if (directions.vertical) {
            SetLeftStickY(coords.axis_my.y);
        }
        if (directions.diagonal) {
            SetLeftStick(coords.quadrant_my);
            if (shield_button_pressed) {
                SetLeftStick(coords.airdodge_quadrant12_my);
                if (directions.y < 0) {
                    SetLeftStick(coords.airdodge_quadrant34_my);
                }
            }
        }

        // Turnaround neutral B nerf
        if (_inputs->b) {
            SetLeftStickX(coords.horizontal_b_my);
        }

        if (directions.diagonal && !shield_button_pressed) {
            SetLeftStick(coords.quadrant_my);
            if (_inputs->c_down) {
                SetLeftStick(coords.quadrant_my_cd);
            }
            if (_inputs->c_left) {
                SetLeftStick(coords.quadrant_my_cl);
            }
            if (_inputs->c_up) {
                SetLeftStick(coords.quadrant_my_cu);
            }
            if (_inputs->c_right) {
                SetLeftStick(coords.quadrant_my_cr);
            }

            if (_inputs->b) {
                SetLeftStick(coords.quadrant_b_my);
                if (_inputs->c_down) {
                    SetLeftStick(coords.quadrant_b_my_cd);
                }
                if (_inputs->c_left) {
                    SetLeftStick(coords.quadrant_b_my_cl);
                }
                if (_inputs->c_up) {
                    SetLeftStick(coords.quadrant_b_my_cu);
                }
                if (_inputs->c_right) {
                    SetLeftStick(coords.quadrant_b_my_cr);
                }
            }
        }
    }

    // C-stick ASDI Slideoff angle overrides any other C-stick modifiers (such as
    // angled fsmash).
    if (directions.cx != 0 && directions.cy != 0) {
        SetCStick(coords.c_quadrant);
    }

    // Horizontal SOCD overrides X-axis modifiers (for ledgedash maximum jump
    // trajectory).
    if (_horizontal_socd && !directions.vertical) {
        SetLeftStickX(coords.horizontal_ledgedash);
    }

    if (_inputs->lightshield) {
        _outputs->triggerRAnalog = coords.trigger_light;
    }
    if (_inputs->midshield) {
        _outputs->triggerRAnalog = coords.trigger_mid;
    }

    if (_outputs->triggerLDigital) {
        _outputs->triggerLAnalog = coords.trigger_hard;
    }

    if (_outputs->triggerRDigital) {
        _outputs->triggerRAnalog = coords.trigger_hard;
    }

    if (_inputs->mod_x && _inputs->mod_y) {
        SetCStick(coords.c_origin);
    }

    // Nunchuk overrides left stick.
    if (_inputs->nunchuk_connected) {
        _outputs->leftStickX = _inputs->nunchuk_x;
        _outputs->leftStickY = _inputs->nunchuk_y;
    }
}
