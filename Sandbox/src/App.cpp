#include "Jerboa.h"
#include "Jerboa/EntryPoint.h"

#include <iostream>

class SandboxApp : public Jerboa::Application
{
public:
	SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp created");
	}

	virtual void OnStart() {
		JERBOA_LOG_INFO("SandboxApp started");
	}

	~SandboxApp()
	{
		JERBOA_LOG_INFO("SanboxApp destroyed");
	}
};

Jerboa::Application* Jerboa::CreateApplication() {
	return new SandboxApp();
}