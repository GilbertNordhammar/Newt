#pragma once

#include "Jerboa/Core/Input.h"

#include "glm/glm.hpp"

#include <memory>

namespace Jerboa {
	class GLFW_Input : public Input
	{
	public:
		virtual void InitImpl() override;
		virtual void UpdateImpl() override;

		virtual bool IsKeyHeldDownImpl(KeyCode key) override;
		virtual bool IsMouseButtonHeldDownImpl(MouseButtonCode key) override;

		virtual glm::vec2 GetMouseMovementImpl() override;
		virtual glm::vec2 GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	private:
		glm::vec2 sCurrentMousePos;
		glm::vec2 sPreviousMousePos;
	};
}


