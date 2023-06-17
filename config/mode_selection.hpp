#ifndef _CONFIG_MODE_SELECTION_HPP
#define _CONFIG_MODE_SELECTION_HPP

#include "core/socd.hpp"
#include "core/state.hpp"
#include "modes/DefaultKeyboardMode.hpp"
#include "modes/SF6KeyboardMode.hpp"
#include "modes/FgcMode.hpp"
#include "modes/Melee20Button.hpp"
#include "modes/MeleeMarth20Button.hpp"
#include "modes/MeleePeach20Button.hpp"
#include "modes/MeleePuff20Button.hpp"
#include "modes/MeleeYoshi20Button.hpp"
#include "modes/RivalsOfAether.hpp"
#include "modes/SF6Mode.hpp"
#include "modes/Secret.hpp"

extern KeyboardMode *current_kb_mode;
uint8_t current_mode_id = 0;

void set_mode(CommunicationBackend *backend, ControllerMode *mode) {
    // Delete keyboard mode in case one is set, so we don't end up getting both controller and
    // keyboard inputs.
    delete current_kb_mode;
    current_kb_mode = nullptr;

    // Set new controller mode.
    backend->SetGameMode(mode);
}

void set_mode(CommunicationBackend *backend, KeyboardMode *mode) {
    // Delete and reassign current keyboard mode.
    delete current_kb_mode;
    current_kb_mode = mode;

    // Unset the current controller mode so backend only gives neutral inputs.
    backend->SetGameMode(nullptr);
}

uint8_t get_mode_id_from_modifiers(InputState &inputs) {
    if (inputs.mod_x && !inputs.mod_y && inputs.start) {
        if (inputs.l)
            return 1;
        if (inputs.left)
            return 2;
        if (inputs.down)
            return 3;
        if (inputs.right)
            return 4;
        if (inputs.b)
            return 5;
    } else if (inputs.mod_y && !inputs.mod_x && inputs.start) {
        if (inputs.l)
            return 6;
        if (inputs.left)
            return 7;
        if (inputs.down)
            return 8;
        if (inputs.right)
            return 9;
        if (inputs.b)
            return 10;
    }

    return 0;
}

uint8_t get_mode_id_from_toggles(InputState &inputs) {
    uint8_t result = 1;

    if (inputs.toggle_dpad)
        result += 3;

    if (inputs.toggle_mode_1)
        result += 1;
    else if (inputs.toggle_mode_2)
        result += 2;

    return result;
}

void select_mode(CommunicationBackend *backend, uint8_t new_mode_id) {
    if (current_mode_id == new_mode_id)
        return;

    switch (new_mode_id) {
        case 1:
            set_mode(backend, new MeleePeach20Button(socd::SOCD_2IP_NO_REAC));
            break;
        case 2:
            set_mode(backend, new MeleePuff20Button(socd::SOCD_2IP_NO_REAC));
            break;
        case 3:
            set_mode(backend, new MeleeYoshi20Button(socd::SOCD_2IP_NO_REAC));
            break;
        case 4:
            set_mode(backend, new Melee20Button(socd::SOCD_2IP_NO_REAC));
            break;
        case 5:
            set_mode(backend, new Secret(socd::SOCD_2IP));
            break;
        case 7:
            set_mode(backend, new DefaultKeyboardMode(socd::SOCD_KEYBOARD));
            break;
        case 8:
            set_mode(backend, new FgcMode(socd::SOCD_NEUTRAL));
            break;
        case 9:
            set_mode(backend, new SF6Mode());
            break;
        case 10:
            set_mode(backend, new SF6KeyboardMode());
            break;
        default:
            return;
    }

    current_mode_id = new_mode_id;
}

void select_mode(CommunicationBackend *backend) {
    select_mode(backend, get_mode_id_from_modifiers(backend->GetInputs()));
}

#endif
