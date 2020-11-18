#include "Jerboa.h"
#include "Jerboa/EntryPoint.h"

#include <iostream>

class SandboxApp : public Jerboa::Application
{
public:
	SandboxApp()
	{
		std::cout << "SanboxApp created" << std::endl;
	}

	virtual void OnStart() {
		std::cout << "SandboxApp started" << std::endl;
	}

	~SandboxApp()
	{
		std::cout << "SanboxApp destroyed" << std::endl;
	}
};

Jerboa::Application* Jerboa::CreateApplication() {
	return new SandboxApp();
}