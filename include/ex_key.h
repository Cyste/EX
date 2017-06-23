/*
	Copyright 2015 Mariusz Dzikowski

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#ifndef EX_KEY_H_
#define EX_KEY_H_

enum {
	EX_KEY_UNKNOWN = -1, /* < Unhandled key */
	EX_KEY_A = 0,        /* < The A key */
	EX_KEY_B,            /* < The B key */
	EX_KEY_C,            /* < The C key */
	EX_KEY_D,            /* < The D key */
	EX_KEY_E,            /* < The E key */
	EX_KEY_F,            /* < The F key */
	EX_KEY_G,            /* < The G key */
	EX_KEY_H,            /* < The H key */
	EX_KEY_I,            /* < The I key */
	EX_KEY_J,            /* < The J key */
	EX_KEY_K,            /* < The K key */
	EX_KEY_L,            /* < The L key */
	EX_KEY_M,            /* < The M key */
	EX_KEY_N,            /* < The N key */
	EX_KEY_O,            /* < The O key */
	EX_KEY_P,            /* < The P key */
	EX_KEY_Q,            /* < The Q key */
	EX_KEY_R,            /* < The R key */
	EX_KEY_S,            /* < The S key */
	EX_KEY_T,            /* < The T key */
	EX_KEY_U,            /* < The U key */
	EX_KEY_V,            /* < The V key */
	EX_KEY_W,            /* < The W key */
	EX_KEY_X,            /* < The X key */
	EX_KEY_Y,            /* < THE Y KEY */
	EX_KEY_Z,            /* < THE Z KEY */
	EX_KEY_NUM0,         /* < THE 0 KEY */
	EX_KEY_NUM1,         /* < THE 1 KEY */
	EX_KEY_NUM2,         /* < THE 2 KEY */
	EX_KEY_NUM3,         /* < THE 3 KEY */
	EX_KEY_NUM4,         /* < THE 4 KEY */
	EX_KEY_NUM5,         /* < THE 5 KEY */
	EX_KEY_NUM6,         /* < THE 6 KEY */
	EX_KEY_NUM7,         /* < THE 7 KEY */
	EX_KEY_NUM8,         /* < THE 8 KEY */
	EX_KEY_NUM9,         /* < THE 9 KEY */
	EX_KEY_ESCAPE,       /* < THE ESCAPE KEY */
	EX_KEY_LCONTROL,     /* < THE LEFT CONTROL KEY */
	EX_KEY_LSHIFT,       /* < THE LEFT SHIFT KEY */
	EX_KEY_LALT,         /* < THE LEFT ALT KEY */
	EX_KEY_LSYSTEM,      /* < THE LEFT OS SPECIFIC KEY: WINDOW (WINDOWS AND LINUX), APPLE (MACOS X), ... */
	EX_KEY_RCONTROL,     /* < THE RIGHT CONTROL KEY */
	EX_KEY_RSHIFT,       /* < THE RIGHT SHIFT KEY */
	EX_KEY_RALT,         /* < THE RIGHT ALT KEY */
	EX_KEY_RSYSTEM,      /* < THE RIGHT OS SPECIFIC KEY: WINDOW (WINDOWS AND LINUX), APPLE (MACOS X), ... */
	EX_KEY_MENU,         /* < THE MENU KEY */
	EX_KEY_LBRACKET,     /* < THE [ KEY */
	EX_KEY_RBRACKET,     /* < THE ] KEY */
	EX_KEY_SEMICOLON,    /* < THE ; KEY */
	EX_KEY_COMMA,        /* < THE , KEY */
	EX_KEY_PERIOD,       /* < THE . KEY */
	EX_KEY_QUOTE,        /* < THE ' KEY */
	EX_KEY_SLASH,        /* < THE / KEY */
	EX_KEY_BACKSLASH,    /* < THE \ KEY */
	EX_KEY_TILDE,        /* < THE ~ KEY */
	EX_KEY_EQUAL,        /* < THE = KEY */
	EX_KEY_DASH,         /* < THE - KEY */
	EX_KEY_SPACE,        /* < THE SPACE KEY */
	EX_KEY_RETURN,       /* < THE RETURN KEY */
	EX_KEY_BACKSPACE,    /* < THE BACKSPACE KEY */
	EX_KEY_TAB,          /* < THE TABULATION KEY */
	EX_KEY_PAGEUP,       /* < THE PAGE UP KEY */
	EX_KEY_PAGEDOWN,     /* < THE PAGE DOWN KEY */
	EX_KEY_END,          /* < THE END KEY */
	EX_KEY_HOME,         /* < THE HOME KEY */
	EX_KEY_INSERT,       /* < THE INSERT KEY */
	EX_KEY_DELETE,       /* < THE DELETE KEY */
	EX_KEY_ADD,          /* < THE + KEY */
	EX_KEY_SUBTRACT,     /* < THE - KEY */
	EX_KEY_MULTIPLY,     /* < THE * KEY */
	EX_KEY_DIVIDE,       /* < THE / KEY */
	EX_KEY_LEFT,         /* < LEFT ARROW */
	EX_KEY_RIGHT,        /* < RIGHT ARROW */
	EX_KEY_UP,           /* < UP ARROW */
	EX_KEY_DOWN,         /* < DOWN ARROW */
	EX_KEY_NUMPAD0,      /* < THE NUMPAD 0 KEY */
	EX_KEY_NUMPAD1,      /* < THE NUMPAD 1 KEY */
	EX_KEY_NUMPAD2,      /* < THE NUMPAD 2 KEY */
	EX_KEY_NUMPAD3,      /* < THE NUMPAD 3 KEY */
	EX_KEY_NUMPAD4,      /* < THE NUMPAD 4 KEY */
	EX_KEY_NUMPAD5,      /* < THE NUMPAD 5 KEY */
	EX_KEY_NUMPAD6,      /* < THE NUMPAD 6 KEY */
	EX_KEY_NUMPAD7,      /* < THE NUMPAD 7 KEY */
	EX_KEY_NUMPAD8,      /* < THE NUMPAD 8 KEY */
	EX_KEY_NUMPAD9,      /* < THE NUMPAD 9 KEY */
	EX_KEY_F1,           /* < THE F1 KEY */
	EX_KEY_F2,           /* < THE F2 KEY */
	EX_KEY_F3,           /* < THE F3 KEY */
	EX_KEY_F4,           /* < THE F4 KEY */
	EX_KEY_F5,           /* < THE F5 KEY */
	EX_KEY_F6,           /* < THE F6 KEY */
	EX_KEY_F7,           /* < THE F7 KEY */
	EX_KEY_F8,           /* < THE F8 KEY */
	EX_KEY_F9,           /* < THE F9 KEY */
	EX_KEY_F10,          /* < THE F10 KEY */
	EX_KEY_F11,          /* < THE F11 KEY */
	EX_KEY_F12,          /* < THE F12 KEY */
	EX_KEY_F13,          /* < THE F13 KEY */
	EX_KEY_F14,          /* < THE F14 KEY */
	EX_KEY_F15,          /* < THE F15 KEY */
	EX_KEY_PAUSE,        /* < THE PAUSE KEY */

	EX_KEY_COUNT      /* < KEEP LAST -- THE TOTAL NUMBER OF KEYBOARD KEYS */
};

EX_API void ex_keyboard_init(void);

EX_API int ex_keyboard_get_state(int key);

EX_API void ex_keyboard_set_state(int key, int state);

#endif