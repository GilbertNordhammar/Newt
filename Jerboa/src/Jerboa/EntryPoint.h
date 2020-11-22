#pragma once
#include "Jerboa/Core/Base.h"
#include "Jerboa/Core/Application.h"

#ifdef JERBOA_PLATFORM_WINDOWS

extern Jerboa::Application* Jerboa::CreateApplication();

int main(int argc, char** argv)
{
    Jerboa::InitializeCore();
	Jerboa::Application* app = Jerboa::CreateApplication(); 
	JERBOA_ASSERT(app, "Jerboa::CreateApplication() must not return null");
	
	app->Run();
	
	delete app;
    Jerboa::ShutdownCore();
}

#endif
