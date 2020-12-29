#pragma once

#include "BaseMouseButtonEvent.h"

namespace Jerboa {
	struct MouseButtonPressedEvent : BaseMouseButtonEvent {
		MouseButtonPressedEvent(MouseButtonCode button, ModifierKeyCode modifiers)
			: BaseMouseButtonEvent(button, modifiers) {}
	};
}