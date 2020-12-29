#pragma once

#include "BaseKeyEvent.h"

namespace Jerboa {
	struct KeyPressedEvent : BaseKeyEvent {
		KeyPressedEvent(KeyCode key, ModifierKeyCode modKey)
			: BaseKeyEvent(key, modKey) {}
	};
}