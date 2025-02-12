#include <drivers/keyboard.h>
#include <drivers/vga.h>

// THANK YOU genai
const unsigned char sc_to_ascii[] = {
    0x00, // 0x00 - Empty
    0x1B, // 0x01 - ESC
    '1',  // 0x02
    '2',  // 0x03
    '3',  // 0x04
    '4',  // 0x05
    '5',  // 0x06
    '6',  // 0x07
    '7',  // 0x08
    '8',  // 0x09
    '9',  // 0x0A
    '0',  // 0x0B
    '-',  // 0x0C
    '=',  // 0x0D
    0x08, // 0x0E - Backspace
    '\t', // 0x0F - Tab
    'q',  // 0x10
    'w',  // 0x11
    'e',  // 0x12
    'r',  // 0x13
    't',  // 0x14
    'y',  // 0x15
    'u',  // 0x16
    'i',  // 0x17
    'o',  // 0x18
    'p',  // 0x19
    '[',  // 0x1A
    ']',  // 0x1B
    '\n', // 0x1C - Enter
    0x00, // 0x1D - Left Control
    'a',  // 0x1E
    's',  // 0x1F
    'd',  // 0x20
    'f',  // 0x21
    'g',  // 0x22
    'h',  // 0x23
    'j',  // 0x24
    'k',  // 0x25
    'l',  // 0x26
    ';',  // 0x27
    '\'', // 0x28
    '`',  // 0x29
    0x00, // 0x2A - Left Shift
    '\\', // 0x2B
    'z',  // 0x2C
    'x',  // 0x2D
    'c',  // 0x2E
    'v',  // 0x2F
    'b',  // 0x30
    'n',  // 0x31
    'm',  // 0x32
    ',',  // 0x33
    '.',  // 0x34
    '/',  // 0x35
    0x00, // 0x36 - Right Shift
    '*',  // 0x37 - Keypad *
    0x00, // 0x38 - Left Alt
    ' ',  // 0x39 - Space
    0x00, // 0x3A - CapsLock
    0x00, // 0x3B - F1
    0x00, // 0x3C - F2
    0x00, // 0x3D - F3
    0x00, // 0x3E - F4
    0x00, // 0x3F - F5
    0x00, // 0x40 - F6
    0x00, // 0x41 - F7
    0x00, // 0x42 - F8
    0x00, // 0x43 - F9
    0x00, // 0x44 - F10
    0x00, // 0x45 - NumLock
    0x00, // 0x46 - ScrollLock
    '7',  // 0x47 - Keypad 7
    '8',  // 0x48 - Keypad 8
    '9',  // 0x49 - Keypad 9
    '-',  // 0x4A - Keypad -
    '4',  // 0x4B - Keypad 4
    '5',  // 0x4C - Keypad 5
    '6',  // 0x4D - Keypad 6
    '+',  // 0x4E - Keypad +
    '1',  // 0x4F - Keypad 1
    '2',  // 0x50 - Keypad 2
    '3',  // 0x51 - Keypad 3
    '0',  // 0x52 - Keypad 0
    '.',  // 0x53 - Keypad .
    0x00, // 0x54
    0x00, // 0x55
    0x00, // 0x56
    0x00, // 0x57 - F11
    0x00  // 0x58 - F12
};

// Shifted keys lookup table
const unsigned char sc_to_ascii_shift[] = {
    0x00, // 0x00 - Empty
    0x1B, // 0x01 - ESC
    '!',  // 0x02
    '@',  // 0x03
    '#',  // 0x04
    '$',  // 0x05
    '%',  // 0x06
    '^',  // 0x07
    '&',  // 0x08
    '*',  // 0x09
    '(',  // 0x0A
    ')',  // 0x0B
    '_',  // 0x0C
    '+',  // 0x0D
    0x08, // 0x0E - Backspace
    '\t', // 0x0F - Tab
    'Q',  // 0x10
    'W',  // 0x11
    'E',  // 0x12
    'R',  // 0x13
    'T',  // 0x14
    'Y',  // 0x15
    'U',  // 0x16
    'I',  // 0x17
    'O',  // 0x18
    'P',  // 0x19
    '{',  // 0x1A
    '}',  // 0x1B
    '\n', // 0x1C - Enter
    0x00, // 0x1D - Left Control
    'A',  // 0x1E
    'S',  // 0x1F
    'D',  // 0x20
    'F',  // 0x21
    'G',  // 0x22
    'H',  // 0x23
    'J',  // 0x24
    'K',  // 0x25
    'L',  // 0x26
    ':',  // 0x27
    '"',  // 0x28
    '~',  // 0x29
    0x00, // 0x2A - Left Shift
    '|',  // 0x2B
    'Z',  // 0x2C
    'X',  // 0x2D
    'C',  // 0x2E
    'V',  // 0x2F
    'B',  // 0x30
    'N',  // 0x31
    'M',  // 0x32
    '<',  // 0x33
    '>',  // 0x34
    '?',  // 0x35
    0x00, // 0x36 - Right Shift
    '*',  // 0x37 - Keypad *
    0x00, // 0x38 - Left Alt
    ' ',  // 0x39 - Space
    0x00, // 0x3A - CapsLock
    0x00, // 0x3B - F1
    0x00, // 0x3C - F2
    0x00, // 0x3D - F3
    0x00, // 0x3E - F4
    0x00, // 0x3F - F5
    0x00, // 0x40 - F6
    0x00, // 0x41 - F7
    0x00, // 0x42 - F8
    0x00, // 0x43 - F9
    0x00, // 0x44 - F10
    0x00, // 0x45 - NumLock
    0x00, // 0x46 - ScrollLock
    '7',  // 0x47 - Keypad 7
    '8',  // 0x48 - Keypad 8
    '9',  // 0x49 - Keypad 9
    '-',  // 0x4A - Keypad -
    '4',  // 0x4B - Keypad 4
    '5',  // 0x4C - Keypad 5
    '6',  // 0x4D - Keypad 6
    '+',  // 0x4E - Keypad +
    '1',  // 0x4F - Keypad 1
    '2',  // 0x50 - Keypad 2
    '3',  // 0x51 - Keypad 3
    '0',  // 0x52 - Keypad 0
    '.',  // 0x53 - Keypad .
    0x00, // 0x54
    0x00, // 0x55
    0x00, // 0x56
    0x00, // 0x57 - F11
    0x00  // 0x58 - F12
};

const uint16_t sc_to_special[] = {
    [0x00] = KEY_NONE,        // Empty
    [0x1D] = KEY_LCTRL,       // Left Control
    [0x2A] = KEY_LSHIFT,      // Left Shift
    [0x36] = KEY_RSHIFT,      // Right Shift
    [0x38] = KEY_LALT,        // Left Alt
    [0x3A] = KEY_CAPS_LOCK,   // Caps Lock
    [0x45] = KEY_NUM_LOCK,    // Num Lock
    [0x46] = KEY_SCROLL_LOCK, // Scroll Lock

    // Function keys
    [0x3B] = KEY_F1,  // F1
    [0x3C] = KEY_F2,  // F2
    [0x3D] = KEY_F3,  // F3
    [0x3E] = KEY_F4,  // F4
    [0x3F] = KEY_F5,  // F5
    [0x40] = KEY_F6,  // F6
    [0x41] = KEY_F7,  // F7
    [0x42] = KEY_F8,  // F8
    [0x43] = KEY_F9,  // F9
    [0x44] = KEY_F10, // F10
    [0x57] = KEY_F11, // F11
    [0x58] = KEY_F12, // F12

    // Extended scancodes (E0 prefix)
    // TODO! if byte recieved from 0x60 is 0xE0, then wait for the next byte to
    // be sent (for the extended keys)
    [0xE0 | 0x1D] = KEY_RCTRL,     // Right Control
    [0xE0 | 0x38] = KEY_RALT,      // Right Alt
    [0xE0 | 0x47] = KEY_HOME,      // Home
    [0xE0 | 0x48] = KEY_UP,        // Up Arrow
    [0xE0 | 0x49] = KEY_PAGE_UP,   // Page Up
    [0xE0 | 0x4B] = KEY_LEFT,      // Left Arrow
    [0xE0 | 0x4D] = KEY_RIGHT,     // Right Arrow
    [0xE0 | 0x4F] = KEY_END,       // End
    [0xE0 | 0x50] = KEY_DOWN,      // Down Arrow
    [0xE0 | 0x51] = KEY_PAGE_DOWN, // Page Down
    [0xE0 | 0x52] = KEY_INSERT,    // Insert
    [0xE0 | 0x53] = KEY_DELETE     // Delete
};

static struct {
    bool lshift;
    bool rshift;
    bool lctrl;
    bool rctrl;
    bool lalt;
    bool ralt;
    bool caps_lock;
    bool num_lock;
    bool scroll_lock;
} modifiers;

// If it returns 0, then it is a modifier/special key
char to_ascii(uint8_t mk)
{
    return (modifiers.lshift || modifiers.rshift) ? sc_to_ascii_shift[mk] : sc_to_ascii[mk];
}

void handle_scancode(uint8_t sc)
{
    bool    is_brk = sc & 0x80;
    uint8_t mk     = sc & 0x7F;

    // quick check for modifiers first
    enum SPECIAL_KEY sk = sc_to_special[mk];
    if (sk != 0) {
        // modifier?
        switch (sk) {
        case KEY_LSHIFT:
            modifiers.lshift = !is_brk;
            return;
        case KEY_RSHIFT:
            modifiers.rshift = !is_brk;
            return;
        case KEY_LCTRL:
            modifiers.lctrl = !is_brk;
            return;
        case KEY_RCTRL:
            modifiers.rctrl = !is_brk;
            return;
        case KEY_LALT:
            modifiers.lalt = !is_brk;
            return;
        case KEY_RALT:
            modifiers.ralt = !is_brk;
            return;
        default:
            // unhandled
        }

        // toggles?
        if (!is_brk) {
            switch (sk) {
            // these ones r toggles
            case KEY_CAPS_LOCK:
                modifiers.caps_lock = !modifiers.caps_lock;
                break;
            case KEY_NUM_LOCK:
                modifiers.num_lock = !modifiers.num_lock;
                break;
            case KEY_SCROLL_LOCK:
                modifiers.scroll_lock = !modifiers.scroll_lock;
                break;
            default:
                // unhandled
            }
        }

        return;
    }

    if (is_brk) {
        // set some state idk
        return;
    }

    char ascii = to_ascii(mk);

    // TODO! events system
    vga_putchar(ascii);
}