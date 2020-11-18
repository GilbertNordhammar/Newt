#pragma once
#include "Jerboa/Core/Base.h"
#include "Jerboa/Core/Application.h"

#ifdef JERBOA_PLATFORM_WINDOWS

extern Jerboa::Application* Jerboa::CreateApplication();

int main(int argc, char** argv)
{
    /*
        TODO: 
        - Init and cleanup
        - Assert if app is null
    */
	Jerboa::Application* app = Jerboa::CreateApplication();
	
	app->Run();
	delete app;
}

#endif
