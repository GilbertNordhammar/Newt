#pragma once

#include "KeyCode.h"

#include "glm/vec2.hpp"

#include <memory>

namespace Jerboa {
	namespace InputInternals {
		void Init();
		void Update();
	}

	class Input
	{
		friend void InputInternals::Init();
		friend void InputInternals::Update();

	public:
		// TBA
		/*static bool IsKeyPressed(KeyCode key) { return sInstance->IsKeyPressedImpl(key); };
		static bool IsKeyReleased(KeyCode key) { return sInstance->IsKeyReleasedImpl(key); };
		static bool IsMouseButtonPressed(MouseButtonCode btn) { return sInstance->IsMouseButtonPressedImpl(btn); };
		static bool IsMouseButtonReleased(MouseButtonCode btn) { return sInstance->IsMouseButtonReleasedImpl(btn); };*/

		static bool IsKeyHeldDown(KeyCode key) { return sInstance->IsKeyHeldDownImpl(key); }
		static bool IsMouseButtonHeldDown(MouseButtonCode btn) { return sInstance->IsMouseButtonHeldDownImpl(btn); }

		static glm::vec2 GetMouseMovement() { return sInstance->GetMouseMovementImpl(); }
		static glm::vec2 GetMousePosition() { return sInstance->GetMousePositionImpl(); }
		static float GetMouseX() { return sInstance->GetMouseXImpl(); }
		static float GetMouseY() { return sInstance->GetMouseYImpl(); }
	protected:
		// TBA
		/*virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual bool IsKeyReleasedImpl(KeyCode key) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseButtonCode key) = 0;
		virtual bool IsMouseButtonReleasedImpl(MouseButtonCode key) = 0;*/

		virtual void InitImpl() {};
		virtual void UpdateImpl() {};

		virtual bool IsKeyHeldDownImpl(KeyCode key) = 0;
		virtual bool IsMouseButtonHeldDownImpl(MouseButtonCode key) = 0;

		virtual glm::vec2 GetMouseMovementImpl() = 0;
		virtual glm::vec2 GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static std::unique_ptr<Input> sInstance;
	};
}


