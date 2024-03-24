#include "modes/GgstKeyboardMode.hpp"

#include "core/socd.hpp"
#include "core/state.hpp"

GgstKeyboardMode::GgstKeyboardMode() {}

void GgstKeyboardMode::UpdateKeys(InputState &inputs) {
    Press(HID_KEY_SHIFT_LEFT, inputs.l);
    Press(HID_KEY_A, inputs.left);
    Press(HID_KEY_S, inputs.down);
    Press(HID_KEY_D, inputs.right);
    Press(HID_KEY_SPACE, inputs.mod_x);
    Press(HID_KEY_ALT_LEFT, inputs.mod_y);
    Press(HID_KEY_NONE, inputs.select);
    Press(HID_KEY_KEYPAD_ENTER, inputs.start);
    Press(HID_KEY_NONE, inputs.home);
    Press(HID_KEY_KEYPAD_7, inputs.r);
    Press(HID_KEY_KEYPAD_8, inputs.y);
    Press(HID_KEY_KEYPAD_9, inputs.lightshield);
    Press(HID_KEY_KEYPAD_SUBTRACT, inputs.midshield);
    Press(HID_KEY_KEYPAD_4, inputs.b);
    Press(HID_KEY_KEYPAD_5, inputs.x);
    Press(HID_KEY_KEYPAD_6, inputs.z);
    Press(HID_KEY_KEYPAD_ADD, inputs.up);
    Press(HID_KEY_ARROW_RIGHT, inputs.c_up);
    Press(HID_KEY_ARROW_UP, inputs.c_left);
    Press(HID_KEY_KEYPAD_0, inputs.c_right);
    Press(HID_KEY_ARROW_DOWN, inputs.a);
    Press(HID_KEY_ARROW_LEFT, inputs.c_down);
}
