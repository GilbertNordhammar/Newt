#include "jerboa-pch.h"
#include "KeyCode.h"

namespace Jerboa {
	std::string GetKeyName(int key)
	{
		switch (key) {
		case JERBOA_KEY_SPACE:
			return "Space";
		case JERBOA_KEY_APOSTROPHE:
			return "\'";
		case JERBOA_KEY_COMMA:
			return ",";
		case JERBOA_KEY_MINUS:
			return "-";
		case JERBOA_KEY_PERIOD:
			return ".";
		case JERBOA_KEY_SLASH:
			return "/";
		case JERBOA_KEY_0:
			return "0";
		case JERBOA_KEY_1:
			return "1";
		case JERBOA_KEY_2:
			return "2";
		case JERBOA_KEY_3:
			return "3";
		case JERBOA_KEY_4:
			return "4";
		case JERBOA_KEY_5:
			return "5";
		case JERBOA_KEY_6:
			return "6";
		case JERBOA_KEY_7:
			return "7";
		case JERBOA_KEY_8:
			return "8";
		case JERBOA_KEY_9:
			return "9";
		case JERBOA_KEY_SEMICOLON:
			return ";";
		case JERBOA_KEY_EQUAL:
			return "=";
		case JERBOA_KEY_A:
			return "A";
		case JERBOA_KEY_B:
			return "B";
		case JERBOA_KEY_C:
			return "C";
		case JERBOA_KEY_D:
			return "D";
		case JERBOA_KEY_E:
			return "E";
		case JERBOA_KEY_F:
			return "F";
		case JERBOA_KEY_G:
			return "G";
		case JERBOA_KEY_H:
			return "H";
		case JERBOA_KEY_I:
			return "I";
		case JERBOA_KEY_J:
			return "J";
		case JERBOA_KEY_K:
			return "K";
		case JERBOA_KEY_L:
			return "L";
		case JERBOA_KEY_M:
			return "M";
		case JERBOA_KEY_N:
			return "N";
		case JERBOA_KEY_O:
			return "O";
		case JERBOA_KEY_P:
			return "P";
		case JERBOA_KEY_Q:
			return "Q";
		case JERBOA_KEY_R:
			return "R";
		case JERBOA_KEY_S:
			return "S";
		case JERBOA_KEY_T:
			return "T";
		case JERBOA_KEY_U:
			return "U";
		case JERBOA_KEY_V:
			return "V";
		case JERBOA_KEY_W:
			return "W";
		case JERBOA_KEY_X:
			return "X";
		case JERBOA_KEY_Y:
			return "Y";
		case JERBOA_KEY_Z:
			return "Z";
		case JERBOA_KEY_LEFT_BRACKET:
			return "[";
		case JERBOA_KEY_BACKSLASH:
			return "Backslash";
		case JERBOA_KEY_RIGHT_BRACKET:
			return "[";
		case JERBOA_KEY_GRAVE_ACCENT:
			return "`";
		case JERBOA_KEY_WORLD_1:
			return "World 1";
		case JERBOA_KEY_WORLD_2:
			return "World 2";
		case JERBOA_KEY_ESCAPE:
			return "Esc";
		case JERBOA_KEY_ENTER:
			return "Enter";
		case JERBOA_KEY_TAB:
			return "Tab";
		case JERBOA_KEY_BACKSPACE:
			return "Backspace";
		case JERBOA_KEY_INSERT:
			return "Insert";
		case JERBOA_KEY_DELETE:
			return "Delete";
		case JERBOA_KEY_RIGHT:
			return "Right";
		case JERBOA_KEY_LEFT:
			return "Left";
		case JERBOA_KEY_DOWN:
			return "Down";
		case JERBOA_KEY_UP:
			return "Up";
		case JERBOA_KEY_PAGE_UP:
			return "Page Up";
		case JERBOA_KEY_PAGE_DOWN:
			return "Page Down";
		case JERBOA_KEY_HOME:
			return "Home";
		case JERBOA_KEY_END:
			return "End";
		case JERBOA_KEY_CAPS_LOCK:
			return "Caps Lock";
		case JERBOA_KEY_SCROLL_LOCK:
			return "Scroll Lock";
		case JERBOA_KEY_NUM_LOCK:
			return "Num Lock";
		case JERBOA_KEY_PRINT_SCREEN:
			return "Print Screen";
		case JERBOA_KEY_PAUSE:
			return "Pause";
		case JERBOA_KEY_F1:
			return "F1";
		case JERBOA_KEY_F2:
			return "F2";
		case JERBOA_KEY_F3:
			return "F3";
		case JERBOA_KEY_F4:
			return "F4";
		case JERBOA_KEY_F5:
			return "F5";
		case JERBOA_KEY_F6:
			return "F6";
		case JERBOA_KEY_F7:
			return "F7";
		case JERBOA_KEY_F8:
			return "F8";
		case JERBOA_KEY_F9:
			return "F9";
		case JERBOA_KEY_F10:
			return "F10";
		case JERBOA_KEY_F11:
			return "F11";
		case JERBOA_KEY_F12:
			return "F12";
		case JERBOA_KEY_F13:
			return "F13";
		case JERBOA_KEY_F14:
			return "F14";
		case JERBOA_KEY_F15:
			return "F15";
		case JERBOA_KEY_F16:
			return "F16";
		case JERBOA_KEY_F17:
			return "F17";
		case JERBOA_KEY_F18:
			return "F18";
		case JERBOA_KEY_F19:
			return "F19";
		case JERBOA_KEY_F20:
			return "F20";
		case JERBOA_KEY_F21:
			return "F21";
		case JERBOA_KEY_F22:
			return "F22";
		case JERBOA_KEY_F23:
			return "F23";
		case JERBOA_KEY_F24:
			return "F24";
		case JERBOA_KEY_F25:
			return "F2";
		case JERBOA_KEY_KP_0:
			return "Keypad 0";
		case JERBOA_KEY_KP_1:
			return "Keypad 1";
		case JERBOA_KEY_KP_2:
			return "Keypad 2";
		case JERBOA_KEY_KP_3:
			return "Keypad 3";
		case JERBOA_KEY_KP_4:
			return "Keypad 4";
		case JERBOA_KEY_KP_5:
			return "Keypad 5";
		case JERBOA_KEY_KP_6:
			return "Keypad 6";
		case JERBOA_KEY_KP_7:
			return "Keypad 7";
		case JERBOA_KEY_KP_8:
			return "Keypad 8";
		case JERBOA_KEY_KP_9:
			return "Keypad 9";
		case JERBOA_KEY_KP_DECIMAL:
			return "Keypad .";
		case JERBOA_KEY_KP_DIVIDE:
			return "Keypad /";
		case JERBOA_KEY_KP_MULTIPLY:
			return "Keypad *";
		case JERBOA_KEY_KP_SUBTRACT:
			return "Keypad -";
		case JERBOA_KEY_KP_ADD:
			return "Keypad +";
		case JERBOA_KEY_KP_ENTER:
			return "Keypad Enter";
		case JERBOA_KEY_KP_EQUAL:
			return "Keypad =";
		case JERBOA_KEY_LEFT_SHIFT:
			return "Left Shift";
		case JERBOA_KEY_LEFT_CONTROL:
			return "Left Ctrl";
		case JERBOA_KEY_LEFT_ALT:
			return "Left Alt";
		case JERBOA_KEY_LEFT_SUPER:
			return "Left Super";
		case JERBOA_KEY_RIGHT_SHIFT:
			return "Right Shift";
		case JERBOA_KEY_RIGHT_CONTROL:
			return "Right Ctrl";
		case JERBOA_KEY_RIGHT_ALT:
			return "Right Alt";
		case JERBOA_KEY_RIGHT_SUPER:
			return "Right Super";
		case JERBOA_KEY_MENU:
			return "Menu";
		default:
			return "Unknown key";
		};
	}
}
