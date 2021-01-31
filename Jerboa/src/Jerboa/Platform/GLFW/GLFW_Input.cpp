#include "jerboa-pch.h"
#include "GLFW_Input.h"

#include "Jerboa/Core/Window.h"

#include "GLFW/glfw3.h"

namespace Jerboa {
	void GLFW_Input::InitImpl()
	{
		sCurrentMousePos = GetMousePositionImpl();
		sPreviousMousePos = sCurrentMousePos;
	}

	void GLFW_Input::UpdateImpl()
	{
		sPreviousMousePos = sCurrentMousePos;
		sCurrentMousePos = GetMousePositionImpl();
	}

	bool GLFW_Input::IsKeyHeldDownImpl(KeyCode key)
	{
		auto keyInt = static_cast<int>(key);
		auto state = glfwGetKey(static_cast<GLFWwindow*>(Window::Get()->GetNativeWindow()), keyInt);

		return state == GLFW_PRESS;
	}

	bool GLFW_Input::IsMouseButtonHeldDownImpl(MouseButtonCode key)
	{
		auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(Window::Get()->GetNativeWindow()), static_cast<int>(key));
		return state == GLFW_PRESS;
	}

	glm::vec2 GLFW_Input::GetMouseMovementImpl()
	{
		glm::vec2 mouseMovement = sCurrentMousePos - sPreviousMousePos;
		mouseMovement.x /= Jerboa::Window::Get()->GetWidth();
		mouseMovement.y /= Jerboa::Window::Get()->GetHeight();

		return mouseMovement;
	}

	glm::vec2 GLFW_Input::GetMousePositionImpl()
	{
		double x, y;
		glfwGetCursorPos(static_cast<GLFWwindow*>(Window::Get()->GetNativeWindow()), &x, &y);

		return { static_cast<float>(x), static_cast<float>(y) };
	}

	float GLFW_Input::GetMouseXImpl() 
	{
		return GetMousePositionImpl().x;
	}

	float GLFW_Input::GetMouseYImpl()
	{
		return GetMousePositionImpl().y;
	}
}

