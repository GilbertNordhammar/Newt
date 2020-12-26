#include "jerboa-pch.h"
#include "Window.h"
#include "Platform/GLFW/GLFWWindow.h"

namespace Jerboa {
	Window* Window::Create(const WindowProps& props) 
	{
		return new GLFW_Window(props);
	}
}