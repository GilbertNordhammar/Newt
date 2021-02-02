#include "jerboa-pch.h"
#include "Time.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Core/Window.h"

#include "GLFW/glfw3.h"

namespace Jerboa {
	static float sPreviousTimestamp = 0.0f;
	static float sCurrentTimestamp = 0.0f;

	void TimeInternals::Update()
	{
		sPreviousTimestamp = sCurrentTimestamp;
		sCurrentTimestamp = Time::GetTime();
	}

	float Time::GetTime()
	{
		auto windowApi = Window::GetApi();

		switch (windowApi) {
			case WindowApi::GLFW: return glfwGetTime();
		}

		JERBOA_ASSERT(true, "No window api has been set or the set api is not handled");
		return 0.0f;
	}

	float Time::GetDeltaTime()
	{
		return sCurrentTimestamp - sPreviousTimestamp;
	}
}


