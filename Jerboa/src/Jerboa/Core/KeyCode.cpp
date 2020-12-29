#include "jerboa-pch.h"
#include "KeyCode.h"

namespace Jerboa {
	std::string GetKeyName(KeyCode key)
	{
		switch (key) {
		case KeyCode::Space:
			return "Space";
		case KeyCode::Apostrophe:
			return "\'";
		case KeyCode::Comma:
			return ",";
		case KeyCode::Minus:
			return "-";
		case KeyCode::Period:
			return ".";
		case KeyCode::Slash:
			return "/";
		case KeyCode::_0:
			return "0";
		case KeyCode::_1:
			return "1";
		case KeyCode::_2:
			return "2";
		case KeyCode::_3:
			return "3";
		case KeyCode::_4:
			return "4";
		case KeyCode::_5:
			return "5";
		case KeyCode::_6:
			return "6";
		case KeyCode::_7:
			return "7";
		case KeyCode::_8:
			return "8";
		case KeyCode::_9:
			return "9";
		case KeyCode::Semicolon:
			return ";";
		case KeyCode::Equal:
			return "=";
		case KeyCode::A:
			return "A";
		case KeyCode::B:
			return "B";
		case KeyCode::C:
			return "C";
		case KeyCode::D:
			return "D";
		case KeyCode::E:
			return "E";
		case KeyCode::F:
			return "F";
		case KeyCode::G:
			return "G";
		case KeyCode::H:
			return "H";
		case KeyCode::I:
			return "I";
		case KeyCode::J:
			return "J";
		case KeyCode::K:
			return "K";
		case KeyCode::L:
			return "L";
		case KeyCode::M:
			return "M";
		case KeyCode::N:
			return "N";
		case KeyCode::O:
			return "O";
		case KeyCode::P:
			return "P";
		case KeyCode::Q:
			return "Q";
		case KeyCode::R:
			return "R";
		case KeyCode::S:
			return "S";
		case KeyCode::T:
			return "T";
		case KeyCode::U:
			return "U";
		case KeyCode::V:
			return "V";
		case KeyCode::W:
			return "W";
		case KeyCode::X:
			return "X";
		case KeyCode::Y:
			return "Y";
		case KeyCode::Z:
			return "Z";
		case KeyCode::LeftBracket:
			return "[";
		case KeyCode::Backslash:
			return "Backslash";
		case KeyCode::RightBracket:
			return "[";
		case KeyCode::GraveAccent:
			return "`";
		case KeyCode::World1:
			return "World 1";
		case KeyCode::World2:
			return "World 2";
		case KeyCode::Escape:
			return "Esc";
		case KeyCode::Enter:
			return "Enter";
		case KeyCode::Tab:
			return "Tab";
		case KeyCode::Backspace:
			return "Backspace";
		case KeyCode::Insert:
			return "Insert";
		case KeyCode::Delete:
			return "Delete";
		case KeyCode::Right:
			return "Right";
		case KeyCode::Left:
			return "Left";
		case KeyCode::Down:
			return "Down";
		case KeyCode::Up:
			return "Up";
		case KeyCode::PageUp:
			return "Page Up";
		case KeyCode::PageDown:
			return "Page Down";
		case KeyCode::Home:
			return "Home";
		case KeyCode::End:
			return "End";
		case KeyCode::CapsLock:
			return "Caps Lock";
		case KeyCode::ScrollLock:
			return "Scroll Lock";
		case KeyCode::NumLock:
			return "Num Lock";
		case KeyCode::PrintScreen:
			return "Print Screen";
		case KeyCode::Pause:
			return "Pause";
		case KeyCode::F1:
			return "F1";
		case KeyCode::F2:
			return "F2";
		case KeyCode::F3:
			return "F3";
		case KeyCode::F4:
			return "F4";
		case KeyCode::F5:
			return "F5";
		case KeyCode::F6:
			return "F6";
		case KeyCode::F7:
			return "F7";
		case KeyCode::F8:
			return "F8";
		case KeyCode::F9:
			return "F9";
		case KeyCode::F10:
			return "F10";
		case KeyCode::F11:
			return "F11";
		case KeyCode::F12:
			return "F12";
		case KeyCode::F13:
			return "F13";
		case KeyCode::F14:
			return "F14";
		case KeyCode::F15:
			return "F15";
		case KeyCode::F16:
			return "F16";
		case KeyCode::F17:
			return "F17";
		case KeyCode::F18:
			return "F18";
		case KeyCode::F19:
			return "F19";
		case KeyCode::F20:
			return "F20";
		case KeyCode::F21:
			return "F21";
		case KeyCode::F22:
			return "F22";
		case KeyCode::F23:
			return "F23";
		case KeyCode::F24:
			return "F24";
		case KeyCode::F25:
			return "F2";
		case KeyCode::KP_0:
			return "Keypad 0";
		case KeyCode::KP_1:
			return "Keypad 1";
		case KeyCode::KP_2:
			return "Keypad 2";
		case KeyCode::KP_3:
			return "Keypad 3";
		case KeyCode::KP_4:
			return "Keypad 4";
		case KeyCode::KP_5:
			return "Keypad 5";
		case KeyCode::KP_6:
			return "Keypad 6";
		case KeyCode::KP_7:
			return "Keypad 7";
		case KeyCode::KP_8:
			return "Keypad 8";
		case KeyCode::KP_9:
			return "Keypad 9";
		case KeyCode::KP_Decimal:
			return "Keypad .";
		case KeyCode::KP_Divide:
			return "Keypad /";
		case KeyCode::KP_Multiply:
			return "Keypad *";
		case KeyCode::KP_Subract:
			return "Keypad -";
		case KeyCode::KP_Add:
			return "Keypad +";
		case KeyCode::KP_Enter:
			return "Keypad Enter";
		case KeyCode::KP_Equal:
			return "Keypad =";
		case KeyCode::LeftShift:
			return "Left Shift";
		case KeyCode::LeftControl:
			return "Left Ctrl";
		case KeyCode::LeftAlt:
			return "Left Alt";
		case KeyCode::LeftSuper:
			return "Left Super";
		case KeyCode::RightShift:
			return "Right Shift";
		case KeyCode::RightControl:
			return "Right Ctrl";
		case KeyCode::RightAlt:
			return "Right Alt";
		case KeyCode::RightSuper:
			return "Right Super";
		case KeyCode::Menu:
			return "Menu";
		};
	}

	bool HasModifier(ModifierKeyCode keys, ModifierKeyCode key)
	{
		return (static_cast<int>(keys) & static_cast<int>(key)) > 0;
	}
}
