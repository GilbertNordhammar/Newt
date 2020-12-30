#pragma once

#include "Jerboa/Event.h"
#include "Jerboa/Core/KeyCode.h"

namespace Jerboa {
	struct BaseMouseButtonEvent : Event {
		BaseMouseButtonEvent(MouseButtonCode button, ModifierKeyCode modifiers)
			: button(button), modifiers(modifiers) {}

		const MouseButtonCode button;
		const ModifierKeyCode modifiers;

		virtual ~BaseMouseButtonEvent() = 0 {}
	};
}