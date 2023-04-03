/*
  Simple Window Module
  Copyright (c) 2023 AlBuSoft (FürthORG) <support@fürth.org>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "swm_begincode.h"

BEGIN_NAMESPACE

/*
* \since This enumeration is available since v1.0.0.
*/
enum class Keys
{
	MOUSE_LEFT = 1,
	MOUSE_RIGHT = 2,
	MOUSE_CANCEL = 3,
	MOUSE_MIDDLE = 4,
	MOUSE_XBUTTON1 = 5,
	MOUSE_XBUTTON2 = 6,

	BACK = 8,
	TAB = 9,

	CLEAR = 12,
	RETURN = 13,

	SHIFT = 16,
	CONTROL = 17,
	MENU = 18,
	PAUSE = 19,
	CAPITAL = 20,

	ESCAPE = 27,

	SPACE = 32,
	NEXT = 34,
	END = 35,
	HOME = 36,
	LEFT = 37,
	UP = 38,
	RIGHT = 39,
	DOWN = 40,
	SELECT = 41,
	PRINT = 42,
	PAGE_UP = 43,
	PAGE_DOWN = 44,
	INSERT = 45,
	DELETE = 46,
	HELP = 47,

	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,

	/*
	 * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	 * 0x3A - 0x40 : unassigned
	 * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	 */

	LEFT_WIN = 91,
	RIGHT_WIN = 92,
	APPS = 93,

	SLEEP = 95,

	NUMPAD0 = 96,
	NUMPAD1 = 97,
	NUMPAD2 = 98,
	NUMPAD3 = 99,
	NUMPAD4 = 100,
	NUMPAD5 = 101,
	NUMPAD6 = 102,
	NUMPAD7 = 103,
	NUMPAD8 = 104,
	NUMPAD9 = 105,

	MULTIPLY = 106,
	ADD = 107,
	SEPERATOR = 108,
	SUBTRACT = 109,
	DECIMAL = 110,
	DIVIDE = 111,

	F1 = 112,
	F2 = 113,
	F3 = 114,
	F4 = 115,
	F5 = 116,
	F6 = 117,
	F7 = 118,
	F8 = 119,
	F9 = 120,
	F10 = 121,
	F11 = 122,
	F12 = 123,
	F13 = 124,
	F14 = 125,
	F15 = 126,
	F16 = 127,
	F17 = 128,
	F18 = 129,
	F19 = 130,
	F20 = 131,
	F21 = 132,
	F22 = 133,
	F23 = 134,
	F24 = 135,

	NUM_LOCK = 144,
	SCROLL = 145,

	LEFT_SHIFT = 160,
	RIGHT_SHIFT = 161,
	LEFT_CONTROL = 162,
	RIGHT_CONTROL = 163,
	/*
	 * Left ALT-Key
	 */
	LEFT_MENU = 164,
	/*
	 * Right ALT-Key
	 */
	RIGHT_MENU = 165,

	VOLUME_MUTE = 173,
	VOLUME_DOWN = 174,
	VOLUME_UP = 175,

	/*
	 * ';:' for US
	 */
	OEM_1 = 186,
	/*
	 * '+' any country
	 */
	OEM_PLUS = 187,
	/*
	 * ',' any country
	 */
	OEM_COMMA = 188,
	/*
	 * '-' any country
	 */
	OEM_MINUS = 189,
	/*
	 * '.' any country
	 */
	OEM_PERIOD = 190,
	/*
	 * '/?' for US
	 */
	OEM_2 = 191,
	/*
	 * '`~' for US
	 */
	OEM_3 = 192,

	GAMEPAD_A = 195,
	GAMEPAD_B = 196,
	GAMEPAD_X = 197,
	GAMEPAD_Y = 198,
	GAMEPAD_RIGHT_SHOULDER = 199,
	GAMEPAD_LEFT_SHOULDER = 200,
	GAMEPAD_LEFT_TRIGGER = 201,
	GAMEPAD_RIGHT_TRIGGER = 202,
	GAMEPAD_DPAD_UP = 203,
	GAMEPAD_DPAD_DOWN = 204,
	GAMEPAD_DPAD_LEFT = 205,
	GAMEPAD_DPAD_RIGHT = 206,
	GAMEPAD_MENU = 207,
	GAMEPAD_VIEW = 208,
	GAMEPAD_LEFT_THUMBSTICK_BUTTON = 209,
	GAMEPAD_RIGHT_THUMBSTICK_BUTTON = 210,
	GAMEPAD_LEFT_THUMBSTICK_UP = 211,
	GAMEPAD_LEFT_THUMBSTICK_DOWN = 212,
	GAMEPAD_LEFT_THUMBSTICK_RIGHT = 213,
	GAMEPAD_LEFT_THUMBSTICK_LEFT = 214,
	GAMEPAD_RIGHT_THUMBSTICK_UP = 215,
	GAMEPAD_RIGHT_THUMBSTICK_DOWN = 216,
	GAMEPAD_RIGHT_THUMBSTICK_RIGHT = 217,
	GAMEPAD_RIGHT_THUMBSTICK_LEFT = 218,

	/*
	 * '[{' for US
	 */
	OEM_4 = 219,
	/*
	 * '\|' for US
	 */
	OEM_5 = 220,
	/*
	 * ']}' for US
	 */
	OEM_6 = 221,
	/*
	 * ''"' for US
	 */
	OEM_7 = 222,
	OEM_8 = 223,
};

/*
* \since This struct is available since v1.0.0.
*/
typedef struct
{
	short key_states[256];
	short old_key_states[256];
} KeyEvent;

typedef enum
{
	WINDOW_CLOSE = 1,
	WINDOW_QUIT,
	WINDOW_SIZE,
	WINDOW_MOVE,
	WINDOW_SETFOCUS,
	WINDOW_KILLFOCUS,
} WindowEventTypes;

/*
* \since This struct is available since v1.0.0.
*/
typedef struct
{
	unsigned int wnd;
	unsigned int type;
} WindowEvent;

/*
* \since This struct is available since v1.0.0.
*/
typedef struct
{
	KeyEvent keys;
	WindowEvent window;
} Event;

/*
* \example void SizeFunction(unsigned int windowId, unsigned long long wparam, int width, int height);
*/
typedef void(*SIZEEVENTFUNCTION)(unsigned int, unsigned long long, int, int);
/*
* \example void SizeFunction(unsigned int windowId, unsigned long long wparam, int x, int y);
*/
typedef void(*MOVEEVENTFUNCTION)(unsigned int, unsigned long long, int, int);
/*
* \example void DrawFunction(unsigned int windowId);
*/
typedef void(*DRAWEVENTFUNCTION)(unsigned int);

/*
* \since This function is available since v1.0.0.
*/
SWM_API void SetSizeEventFunction(unsigned int window, SIZEEVENTFUNCTION func);
/*
* \since This function is available since v1.0.0.
*/
SWM_API void SetMoveEventFunction(unsigned int window, MOVEEVENTFUNCTION func);
/*
* \since This function is available since v1.0.0.
*/
SWM_API void SetDrawEventFunction(unsigned int window, DRAWEVENTFUNCTION func);

/*
* \since This function is available since v1.0.0.
*/
SWM_API bool PollEvents(Event& e);

/**
* This function checks if the KeyCode key is pass through down.
*
* \returns true while key with KeyCode key is down.
*
* \since This function is available since v1.0.0
*/
SWM_API bool KeyIsDown(Keys key);

/**
* This function checks if the KeyCode key is pass through up.
*
* \returns true while key with KeyCode key is up.
*
* \since This function is available since v1.0.0
*/
SWM_API bool KeyIsUp(Keys key);

/**
* This function checks if the KeyCode key is down the first time.
*
* \returns true if key with KeyCode key is first time down.
*
* \since This function is available since v1.0.0
*/
SWM_API bool OnKeyDown(Keys key);

/**
* This function checks if the KeyCode key is up the first time.
*
* \returns true if key with KeyCode key is first time up.
*
* \since This function is available since v1.0.0
*/
SWM_API bool OnKeyUp(Keys key);

END_NAMESPACE

#include "swm_endcode.h"
