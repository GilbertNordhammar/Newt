#include "jerboa-pch.h"
#include "Input.h"

#include "Jerboa/Platform/GLFW/GLFW_Input.h"

namespace Jerboa {
	std::unique_ptr<Input> Input::sInstance = std::make_unique<GLFW_Input>(); // TODO: Make make API check

	namespace InputInternals {
		void Init()
		{
			Input::sInstance->InitImpl();
		}
		void Update()
		{
			Input::sInstance->UpdateImpl();
		}
	}
}