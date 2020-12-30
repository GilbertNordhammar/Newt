#pragma once

#include "Jerboa/Core/Event.h"

namespace Jerboa {
	struct MouseMovedEvent : Event {
		MouseMovedEvent(int x, int y)
			: x(x), y(y) {}
		const int x, y;
	};
}
