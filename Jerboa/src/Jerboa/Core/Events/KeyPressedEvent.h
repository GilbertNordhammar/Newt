#pragma once

#include "Jerboa/Core/Event.h"
#include <string>

namespace Jerboa {
	struct KeyPressedEvent : Event {
		KeyPressedEvent(int key, std::string keyName)
			: key(key), keyName(keyName) {}

		const int key;
		const std::string keyName;
	};
}
