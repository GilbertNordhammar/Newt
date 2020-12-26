#include "jerboa-pch.h"
#include "GLFWWindow.h"
#include "Jerboa/Debug.h"

namespace Jerboa {
	GLFWWindow::GLFWWindow(const WindowProps& props)
	{
		Init(props);
	}

	void GLFWWindow::OnUpdate()
	{

	}

	WindowPosition GLFWWindow::GetPosition() const
	{
		return WindowPosition();
	}

	void GLFWWindow::SetVSync(bool enabled)
	{

	}

	void GLFWWindow::Init(const WindowProps& props)
	{
		mData.height = props.height;
		mData.width = props.width;
		mData.title = mData.title;

		JERBOA_LOG_INFO("Creating window {0} ({1}x{2})", props.title, props.width, props.height);
	}
}

