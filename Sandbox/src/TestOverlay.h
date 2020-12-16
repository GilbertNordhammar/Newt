#pragma once

#include "Jerboa.h"
#include "Jerboa/Core/Layer.h"
#include "Jerboa/Event.h"
#include "Events/MessageEvent.h"
#include <string>

class TestOverlay : public Jerboa::Layer
{
public:
	TestOverlay() {
		mNumbering = GetNumbering();
	}

	virtual void OnAttach() override {
		JERBOA_LOG_INFO("TestOverlay {} attached", mNumbering);
	}

	virtual void OnDetach() override {
		JERBOA_LOG_INFO("TestOverlay {} deattached", mNumbering);
	}

	void SendMessage(const std::string& message) {
		Jerboa::EventBus::Get()->Publish(MessageEvent(message, "TestOverlay " + std::to_string(mNumbering)));
	}
private:
	int mNumbering;

	static int GetNumbering() {
		static int instanceCount;
		return instanceCount++;
	}
	
};

