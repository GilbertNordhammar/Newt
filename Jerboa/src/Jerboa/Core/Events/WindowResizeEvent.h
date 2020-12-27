#pragma once

#include "Jerboa/Event.h"

namespace Jerboa {
	struct WindowResizeEvent : public Event {
		WindowResizeEvent(int width, int height)
			: width(width), height(height) {}

		int width, height;
	};
}
