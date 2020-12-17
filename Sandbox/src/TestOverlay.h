#pragma once

#include "Jerboa.h"
#include "Jerboa/Core/Layer.h"
#include "Jerboa/Event.h"
#include "Events/MessageEvent.h"
#include "Events/ExternalMessageEvent.h"
#include <string>

class TestOverlay : public Jerboa::Layer
{
public:
	TestOverlay() 
		: mExternalMessageObserver(Jerboa::EventObserver::Create(GetSharedEventBus(), this, &TestOverlay::OnExternalMessageEvent))
	{
		mNumbering = GetNumbering();
	}

	void OnExternalMessageEvent(const ExternalMessageEvent& evnt) {
		JERBOA_LOG_TRACE("TestOverlay {} received message \"{}\" from \"{}\"", mNumbering, evnt.mMessage, evnt.mSender);
	}

	virtual void OnAttach() override {
		JERBOA_LOG_INFO("TestOverlay {} attached", mNumbering);
	}

	virtual void OnDetach() override {
		JERBOA_LOG_INFO("TestOverlay {} deattached", mNumbering);
	}

	void SendMessageEvent(const std::string& message) {
		GetSharedEventBus()->Publish(MessageEvent(message, "TestOverlay " + std::to_string(mNumbering)));
	}
private:
	static int GetNumbering() {
		static int instanceCount;
		return instanceCount++;
	}

	Jerboa::EventObserver mExternalMessageObserver;
	int mNumbering;
};

