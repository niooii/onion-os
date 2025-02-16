#pragma once

#include <def.h>

// just PS2 scan code set 1 for now

enum SPECIAL_ASCII {
    ASCII_ESCAPE    = 0x1B,
    ASCII_BACKSPACE = 0x08,
    ASCII_TAB       = '\t',
    ASCII_ENTER     = 0x0D,
    ASCII_NEWLINE   = '\n',
};

// Defs to be used in application and stuff
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

// later for someday when i decimde to store key states
enum STANDARD_KEY {
    KEY_SPACE       = 0x20, // 32
    KEY_EXCLAMATION = 0x21, // !
    KEY_QUOTE       = 0x22, // "
    KEY_HASH        = 0x23, // #
    KEY_DOLLAR      = 0x24, // $
    KEY_PERCENT     = 0x25, // %
    KEY_AMPERSAND   = 0x26, // &
    KEY_APOSTROPHE  = 0x27, // '
    KEY_LEFT_PAREN  = 0x28, // (
    KEY_RIGHT_PAREN = 0x29, // )
    KEY_ASTERISK    = 0x2A, // *
    KEY_PLUS        = 0x2B, // +
    KEY_COMMA       = 0x2C, // ,
    KEY_MINUS       = 0x2D, // -
    KEY_PERIOD      = 0x2E, // .
    KEY_SLASH       = 0x2F, // /

    KEY_0 = 0x30,
    KEY_1 = 0x31,
    KEY_2 = 0x32,
    KEY_3 = 0x33,
    KEY_4 = 0x34,
    KEY_5 = 0x35,
    KEY_6 = 0x36,
    KEY_7 = 0x37,
    KEY_8 = 0x38,
    KEY_9 = 0x39,

    KEY_COLON     = 0x3A, // :
    KEY_SEMICOLON = 0x3B, // ;
    KEY_LESS      = 0x3C, // <
    KEY_EQUALS    = 0x3D, // =
    KEY_GREATER   = 0x3E, // >
    KEY_QUESTION  = 0x3F, // ?
    KEY_AT        = 0x40, // @

    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,

    KEY_LEFT_BRACKET  = 0x5B, // [
    KEY_BACKSLASH     = 0x5C, //
    KEY_RIGHT_BRACKET = 0x5D, // ]
    KEY_CARET         = 0x5E, // ^
    KEY_UNDERSCORE    = 0x5F, // _
    KEY_BACKTICK      = 0x60, // `

    KEY_a = 0x61,
    KEY_b = 0x62,
    KEY_c = 0x63,
    KEY_d = 0x64,
    KEY_e = 0x65,
    KEY_f = 0x66,
    KEY_g = 0x67,
    KEY_h = 0x68,
    KEY_i = 0x69,
    KEY_j = 0x6A,
    KEY_k = 0x6B,
    KEY_l = 0x6C,
    KEY_m = 0x6D,
    KEY_n = 0x6E,
    KEY_o = 0x6F,
    KEY_p = 0x70,
    KEY_q = 0x71,
    KEY_r = 0x72,
    KEY_s = 0x73,
    KEY_t = 0x74,
    KEY_u = 0x75,
    KEY_v = 0x76,
    KEY_w = 0x77,
    KEY_x = 0x78,
    KEY_y = 0x79,
    KEY_z = 0x7A,

    KEY_LEFT_BRACE  = 0x7B, // {
    KEY_PIPE        = 0x7C, // |
    KEY_RIGHT_BRACE = 0x7D, // }
    KEY_TILDE       = 0x7E  // ~
};

void handle_scancode(uint8_t sc);