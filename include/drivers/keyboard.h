#pragma once

#include <def.h>

// just PS2 scan code set 1 for now

enum SPECIAL_KEYS {
    KEY_NONE = 0,
    // Modifier keys
    KEY_LCTRL = 0x100,
    KEY_LSHIFT,
    KEY_LALT,
    KEY_LGUI,
    KEY_RCTRL,
    KEY_RSHIFT,
    KEY_RALT,
    KEY_RGUI,
    KEY_CAPS_LOCK,
    KEY_NUM_LOCK,
    KEY_SCROLL_LOCK,
    // Function keys
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    // Navigation cluster
    KEY_PRINT_SCREEN,
    KEY_PAUSE,
    KEY_INSERT,
    KEY_DELETE,
    KEY_HOME,
    KEY_END,
    KEY_PAGE_UP,
    KEY_PAGE_DOWN,
    // Arrow keys
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
};

void handle_scancode(uint8_t sc);