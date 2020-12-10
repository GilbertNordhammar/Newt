#include "Jerboa.h"
#include "Jerboa/EntryPoint.h"

static class TestEvent : public Jerboa::Event {
public:
	TestEvent(int value) : mValue(value) {}
	int mValue;
};
//class TestEvent {};

class TestSubscriber {
public:
	TestSubscriber(Jerboa::EventBus* eventBus, std::string message) : mMessage(message), mTestEventObserver(eventBus) {
		mTestEventObserver.OnEvent(this, &TestSubscriber::OnTestEvent);
	}

private:
	void OnTestEvent(const TestEvent& evnt) {
		JERBOA_LOG_ERROR("Message: {}  Value: {}", mMessage, evnt.mValue);
	}

	std::string mMessage;
	Jerboa::EventObserver<TestSubscriber, TestEvent> mTestEventObserver;
};

class SandboxApp : public Jerboa::Application
{
public:
	SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp created");
	}

	virtual void OnStart() {
		JERBOA_LOG_INFO("SandboxApp started");
		
		TestSubscriber s1(&mEventBus, "S1 received TestEvent");
		{
			TestSubscriber s2(&mEventBus, "S2 received TestEvent");
			mEventBus.Publish<TestEvent>(new TestEvent(1));
		}
		
		mEventBus.Publish<TestEvent>(new TestEvent(2));
	}

	~SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp destroyed");
	}


private:
	Jerboa::EventBus mEventBus;
};

Jerboa::Application* Jerboa::CreateApplication() {
	return new SandboxApp();
}