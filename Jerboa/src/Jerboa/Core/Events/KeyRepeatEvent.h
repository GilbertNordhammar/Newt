#pragma once

#include "BaseKeyEvent.h"

namespace Jerboa {
	struct KeyRepeatEvent : BaseKeyEvent {
		KeyRepeatEvent(KeyCode key, ModifierKeyCode modKey)
			: BaseKeyEvent(key, modKey) {}
	};
}
