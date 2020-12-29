#include "Jerboa/Core/Event.h"

namespace Jerboa {
	struct MouseScrolledEvent : Event {
		MouseScrolledEvent(int xOffset, int yOffset)
			: xOffset(xOffset), yOffset(yOffset) {}
		const int xOffset, yOffset;
	};
}
#pragma once
