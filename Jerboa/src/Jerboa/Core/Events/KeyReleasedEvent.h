#pragma once

#include "BaseKeyEvent.h"

namespace Jerboa {
	struct KeyReleasedEvent : BaseKeyEvent {
		KeyReleasedEvent(KeyCode key, ModifierKeyCode modKey)
			: BaseKeyEvent(key, modKey) {}
	};
}