#include "jerboa-pch.h"
#include "GLFW_Window.h"
#include "Jerboa/Debug.h"
#include "Jerboa/Core/KeyCode.h"
#include "Jerboa/Core/Events/WindowResizeEvent.h"
#include "Jerboa/Core/Events/WindowCloseEvent.h"
#include "Jerboa/Core/Events/KeyPressedEvent.h"
#include "Jerboa/Core/Events/KeyReleasedEvent.h"
#include "Jerboa/Core/Events/KeyRepeatEvent.h"
#include "Jerboa/Core/Events/MouseMovedEvent.h"
#include "Jerboa/Core/Events/MouseScrolledEvent.h"
#include "Jerboa/Core/Events/MouseButtonPressedEvent.h"
#include "Jerboa/Core/Events/MouseButtonReleasedEvent.h"

namespace Jerboa {
	static void GLFWErrorCallback(int error, const char* description)
	{
		JERBOA_LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	static bool sGLFWInitialized = false;

	GLFW_Window::GLFW_Window(const WindowProps& props)
	{
		Init(props);
	}

	GLFW_Window::~GLFW_Window()
	{
		ShutDown();
	}

	void GLFW_Window::OnUpdate()
	{
		glfwSwapBuffers(mWindow);
		glfwPollEvents();
	}

	WindowPosition GLFW_Window::GetPosition() const
	{
		// TODO
		return WindowPosition();
	}

	void GLFW_Window::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
		mData.VSync = enabled;
	}

	void GLFW_Window::Init(const WindowProps& props)
	{
		mData.height = props.height;
		mData.width = props.width;
		mData.title = mData.title;

		JERBOA_LOG_INFO("Creating window \"{0}\" ({1}x{2})", props.title, props.width, props.height);

		if (!sGLFWInitialized) {
			int success = glfwInit();
			JERBOA_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);

			sGLFWInitialized = true;
		}

		mWindow = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);
		JERBOA_ASSERT(mWindow, "Could not create GLFW window!");

		glfwMakeContextCurrent(mWindow);
		glfwSetWindowUserPointer(mWindow, &mData);
		glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		glfwSetWindowSizeCallback(mWindow, [](NativeGLFWWindow* window, int width, int height)
		{
				auto& data = *((WindowData*)glfwGetWindowUserPointer(window));

				data.width = width;
				data.height = height;
				data.eventBus->Publish(WindowResizeEvent(width, height));
		});

		glfwSetWindowCloseCallback(mWindow, [](NativeGLFWWindow* window)
		{
			auto& data = *((WindowData*)glfwGetWindowUserPointer(window));

			WindowCloseEvent event;
			data.eventBus->Publish(WindowCloseEvent());
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *((WindowData*)glfwGetWindowUserPointer(window));
			auto keyCode = static_cast<KeyCode>(key);
			auto modsKeyCode = static_cast<ModifierKeyCode>(mods);

			switch (action)
			{
				case GLFW_PRESS:
				{
					data.eventBus->Publish(KeyPressedEvent(keyCode, modsKeyCode));
					break;
				}
				case GLFW_RELEASE:
				{
					data.eventBus->Publish(KeyReleasedEvent(keyCode, modsKeyCode));
					break;
				}
				case GLFW_REPEAT:
				{
					data.eventBus->Publish(KeyRepeatEvent(keyCode, modsKeyCode));
					break;
				}
			}
		});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double x, double y)
		{
			auto& data = *((WindowData*)glfwGetWindowUserPointer(window));
			data.eventBus->Publish(MouseMovedEvent(x, y));
		});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *((WindowData*)glfwGetWindowUserPointer(window));
			data.eventBus->Publish(MouseScrolledEvent(xOffset, yOffset));
		});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto& data = *((WindowData*)glfwGetWindowUserPointer(window));
				auto buttonCode = static_cast<MouseButtonCode>(button);
				auto modsKeyCode = static_cast<ModifierKeyCode>(mods);

				switch (action)
				{
					case GLFW_PRESS:
					{
						data.eventBus->Publish(MouseButtonPressedEvent(buttonCode, modsKeyCode));
						break;
					}
					case GLFW_RELEASE:
					{
						data.eventBus->Publish(MouseButtonReleasedEvent(buttonCode, modsKeyCode));
						break;
					}
				}
			});
	}

	void GLFW_Window::ShutDown()
	{
		glfwTerminate(); // maybe put this at the very end of the program in case there are multiple windows
	}
}

