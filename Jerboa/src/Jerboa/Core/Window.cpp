#include "jerboa-pch.h"
#include "Window.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/GLFW/GLFW_Window.h"

namespace Jerboa {
	std::shared_ptr<Window> Window::sWindow;

	Window* Window::Create(const WindowProps& props)
	{
		JERBOA_ASSERT(!sWindow, "Can't create multiple windows");
		sWindow = std::make_shared<GLFW_Window>(props);
		
		return sWindow.get();
	}

	Window* Window::Get()
	{ 
		JERBOA_ASSERT(sWindow, "The window hasn't been created yet! Is this function called in a static constructor?");
		return sWindow.get();
	}
}