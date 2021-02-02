#include "jerboa-pch.h"
#include "Window.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/GLFW/GLFW_Window.h"

namespace Jerboa {
	std::shared_ptr<Window> Window::sWindow;
	WindowApi Window::sWindowApi = WindowApi::None;

	Window* Window::Create(const WindowProps& props)
	{
		JERBOA_ASSERT(!sWindow, "Can't create multiple windows");

		switch (GetApi()) {
			case WindowApi::GLFW: 
				sWindow = std::make_shared<GLFW_Window>(props); 
				break;
		}

		JERBOA_ASSERT(sWindow, "Window API has not been set or the set API is not handled");
		return sWindow.get();
	}

	Window* Window::Get()
	{ 
		JERBOA_ASSERT(sWindow, "The window hasn't been created yet! Is this function called in a static constructor?");
		return sWindow.get();
	}
}