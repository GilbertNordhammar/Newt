#include "jerboa-pch.h"
#include "Window.h"
#include "Jerboa/Platform/GLFW/GLFW_Window.h"

namespace Jerboa {
	Window* Window::Create(const WindowProps& props) 
	{
		return new GLFW_Window(props);
	}
}