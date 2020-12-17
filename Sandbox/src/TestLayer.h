#pragma once

#include "Jerboa.h"
#include "Jerboa/Core/Layer.h"
#include "Jerboa/Event.h"
#include "Events/MessageEvent.h"
#include "Events/ExternalMessageEvent.h"

class TestLayer : public Jerboa::Layer
{
public:
	TestLayer()
		: mMessageObserver(Jerboa::EventObserver::Create(GetSharedEventBus(), this, &TestLayer::OnMessageEvent)),
		mExternalMessageObserver(Jerboa::EventObserver::Create(GetSharedEventBus(), this, &TestLayer::OnExternalMessageEvent))
	{
		mNumbering = GetNumbering();
	}

	void OnExternalMessageEvent(const ExternalMessageEvent& evnt) {
		JERBOA_LOG_TRACE("TestLayer {} received message \"{}\" from \"{}\"", mNumbering, evnt.mMessage, evnt.mSender);
	}

	void OnMessageEvent(const MessageEvent& evnt) {
		JERBOA_LOG_TRACE("TestLayer {} received message \"{}\" from \"{}\"", mNumbering, evnt.mMessage, evnt.mSender);
	}

	virtual void OnAttach() override {
		JERBOA_LOG_INFO("TestLayer {} attached", mNumbering);
	}

	virtual void OnDetach() override {
		JERBOA_LOG_INFO("TestLayer {} deattached", mNumbering);
	}
private:
	static int GetNumbering() {
		static int instanceCount;
		return instanceCount++;
	}

	int mNumbering;
	Jerboa::EventObserver mMessageObserver;
	Jerboa::EventObserver mExternalMessageObserver;
};

