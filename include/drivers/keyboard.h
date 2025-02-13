#pragma once

#include <def.h>

// just PS2 scan code set 1 for now

// unrelated defs
enum SPECIAL_KEY {
    SK_NONE = 0,
    // Modifier keys
    SK_LCTRL = 0x100,
    SK_LSHIFT,
    SK_LALT,
    SK_LGUI,
    SK_RCTRL,
    SK_RSHIFT,
    SK_RALT,
    SK_RGUI,
    SK_CAPS_LOCK,
    SK_NUM_LOCK,
    SK_SCROLL_LOCK,
    // Control keys
    SK_ESCAPE,
    SK_BACKSPACE,
    SK_TAB,
    SK_ENTER,
    // Function keys
    SK_F1,
    SK_F2,
    SK_F3,
    SK_F4,
    SK_F5,
    SK_F6,
    SK_F7,
    SK_F8,
    SK_F9,
    SK_F10,
    SK_F11,
    SK_F12,
    // Navigation cluster
    SK_PRINT_SCREEN,
    SK_PAUSE,
    SK_INSERT,
    SK_DELETE,
    SK_HOME,
    SK_END,
    SK_PAGE_UP,
    SK_PAGE_DOWN,
    // Arrow keys
    SK_UP,
    SK_DOWN,
    SK_LEFT,
    SK_RIGHT
};

void handle_scancode(uint8_t sc);