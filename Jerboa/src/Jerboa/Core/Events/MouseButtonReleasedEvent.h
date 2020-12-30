#pragma once

#include "BaseMouseButtonEvent.h"

namespace Jerboa {
	struct MouseButtonReleasedEvent : BaseMouseButtonEvent {
		MouseButtonReleasedEvent(MouseButtonCode button, ModifierKeyCode modifiers)
			: BaseMouseButtonEvent(button, modifiers) {}
	};
}