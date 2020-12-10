#include "Jerboa.h"
#include "Jerboa/EntryPoint.h"

static class TestEvent : public Jerboa::Event {};
//class TestEvent {};

class TestSubscriber {
public:
	TestSubscriber(Jerboa::EventBus* eventBus, std::string message) : mMessage(message), mTestEventObserver(eventBus) {
		//eventBus->Subscribe(this, &TestSubscriber::OnTestEvent);
		mTestEventObserver.OnEvent(this, &TestSubscriber::OnTestEvent);
	}

private:
	void OnTestEvent(TestEvent* evnt) {
		JERBOA_LOG_INFO(mMessage);
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
		//{
			//TestSubscriber s2(&mEventBus, "S2 received TestEvent");
		//}
		
		mEventBus.Publish(new TestEvent());
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