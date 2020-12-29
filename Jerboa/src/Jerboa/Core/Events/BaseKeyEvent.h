#pragma once

#include "Jerboa/Core/Event.h"
#include "Jerboa/Core/KeyCode.h"

namespace Jerboa {
	struct BaseKeyEvent : Event {
		BaseKeyEvent(KeyCode key, ModifierKeyCode mods)
			: key(key), modifiers(mods) {}

		const KeyCode key;
		const ModifierKeyCode modifiers;

		virtual ~BaseKeyEvent() = 0 {}
	};
}
