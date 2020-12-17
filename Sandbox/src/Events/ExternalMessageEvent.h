#pragma once

#include "Jerboa/Core/Event.h"
#include "MessageEvent.h"
#include <string>

class ExternalMessageEvent : public MessageEvent {
public:
	ExternalMessageEvent(const std::string& message, const std::string& sender) 
		: MessageEvent(message, sender) {}
};

