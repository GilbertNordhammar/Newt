#include "Jerboa.h"
#include "Jerboa/EntryPoint.h"

struct TestEvent : public Jerboa::Event {
	int mValue = 0;
};
struct HappyEvent : public TestEvent {
	HappyEvent(int value) {
		mValue = value;
	}
};
struct AngryEvent : public TestEvent {
	AngryEvent(int value) {
		mValue = value;
	}
};

class TestSubscriber {
public:
	TestSubscriber(Jerboa::EventBus* eventBus, std::string message) 
		: mMessage(message), 
		mHappyEventObserver(eventBus, this, &TestSubscriber::OnHappyEvent),
		mAngryEventObserver(eventBus, this, &TestSubscriber::OnAngryEvent)
	{}

private:
	void OnHappyEvent(const HappyEvent& evnt) {
		JERBOA_LOG_INFO("HappyEvent | Message: {} | Value: {}", mMessage, evnt.mValue);
	}

	void OnAngryEvent(const AngryEvent& evnt) {
		JERBOA_LOG_INFO("AngryEvent | Message: {} | Value: {}", mMessage, evnt.mValue);
	}

	std::string mMessage;
	Jerboa::EventObserver<TestSubscriber, HappyEvent> mHappyEventObserver;
	Jerboa::EventObserver<TestSubscriber, AngryEvent> mAngryEventObserver;
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
		
		auto eventBus = Jerboa::EventBus::Get();

		TestSubscriber s1(eventBus, "S1");
		{
			TestSubscriber s2(eventBus, "S2");
			eventBus->Publish(HappyEvent(1));
		}
		
		eventBus->Publish(HappyEvent(2));
		eventBus->Publish(AngryEvent(1337));
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