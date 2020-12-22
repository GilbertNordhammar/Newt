#pragma once

/*
	This file is to be included in client applications ONLY
	NEVER include this file anywhere in the engine codebase
*/

#include "Jerboa/Core/Base.h"
#include "Jerboa/Core/Application.h"
#include "Jerboa/Core/Assert.h"

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
