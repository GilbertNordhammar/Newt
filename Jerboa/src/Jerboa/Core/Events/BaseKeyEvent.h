#pragma once

#include "Jerboa/Core/Event.h"
#include "Jerboa/Core/KeyCode.h"

namespace Jerboa {
	struct BaseKeyEvent : Event {
		BaseKeyEvent(KeyCode key, ModifierKeyCode modKey)
			: key(key), modKey(modKey) {}

		const KeyCode key;
		const ModifierKeyCode modKey;

		virtual ~BaseKeyEvent() = 0 {}
	};
}
