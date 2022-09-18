#include "jerboa-pch.h"
#include "Window.h"

#include "Jerboa/Debug.h"
#include "Jerboa/Platform/GLFW/GLFW_Window.h"
#include "Jerboa/Rendering/Renderer.h"

namespace Jerboa {
	std::shared_ptr<Window> Window::sm_Window;
	WindowApi Window::sm_WindowApi = WindowApi::None;

	Window* Window::Create(const WindowProps& props)
	{
		JERBOA_ASSERT(!sm_Window, "Can't create multiple windows");

		switch (GetApi()) {
			case WindowApi::GLFW: 
				sm_Window = std::make_shared<GLFW_Window>(props); 
				break;
		}

		JERBOA_ASSERT(sm_Window, "Window API has not been set or the set API is not handled");
		return sm_Window.get();
	}

	Window* Window::Get()
	{ 
		JERBOA_ASSERT(sm_Window, "The window hasn't been created yet! Is this function called in a static constructor?");
		return sm_Window.get();
	}
}