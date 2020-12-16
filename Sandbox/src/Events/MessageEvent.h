#pragma once

#include "Jerboa/Core/Event.h"
#include <string>

class MessageEvent : public Jerboa::Event
{
public:
	MessageEvent(const std::string& message, const std::string& sender) {
		mMessage = message;
		mSender = sender;
	}

	std::string mMessage;
	std::string mSender;
};

