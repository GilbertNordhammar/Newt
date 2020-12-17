#include "Jerboa.h"
#include "Jerboa/EntryPoint.h"
#include "Jerboa/Core/Layer.h"
#include "TestLayer.h"
#include "TestOverlay.h"
#include "Events/ExternalMessageEvent.h"

class SandboxApp : public Jerboa::Application
{
public:
	SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp created");
	}

	virtual void OnStart() {
		JERBOA_LOG_INFO("SandboxApp started");
		
		auto* testOverlay = new TestOverlay();
		PushOverlay(testOverlay);
		PushLayer(new TestLayer());
		PushLayer(new TestLayer());
		
		testOverlay->SendMessageEvent("yoooo");
		Jerboa::Layer::PublishSharedEvent(ExternalMessageEvent("hiiii", "SandBoxApp"));
	}

	~SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp destroyed");
	}
};

Jerboa::Application* Jerboa::CreateApplication() {
	return new SandboxApp();
}