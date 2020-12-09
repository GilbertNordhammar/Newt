#include "Jerboa.h"
#include "Jerboa/EntryPoint.h"

static class TestEvent : public Jerboa::Event {};
//class TestEvent {};

class SandboxApp : public Jerboa::Application
{
public:
	SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp created");
	}

	virtual void OnStart() {
		JERBOA_LOG_INFO("SandboxApp started");
		mEventBus.Subscribe(this, &SandboxApp::onTestEvent);
		mEventBus.Publish(new TestEvent());
		//mEventBus.Unsubscribe<TestEvent>(this);
		mEventBus.Publish(new TestEvent());
	}

	~SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp destroyed");
	}


private:
	void onTestEvent(TestEvent* evnt) {
		JERBOA_LOG_INFO("TestEvent recieved");
	}

	Jerboa::EventBus mEventBus;
};

Jerboa::Application* Jerboa::CreateApplication() {
	return new SandboxApp();
}