#pragma once

#pragma once

#pragma once

#include "Jerboa/Core/Event.h"
#include <string>

namespace Jerboa {
	struct KeyRepeatEvent : Event {
		KeyRepeatEvent(int key, std::string keyName)
			: key(key), keyName(keyName) {}

		const int key;
		const std::string keyName;
	};
}
