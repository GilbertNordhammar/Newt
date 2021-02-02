#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Jerboa/Core/Window.h"
#include "Jerboa/Debug.h"

namespace Jerboa::UI {
	namespace ImGuiApp {
		void Init(Window* window);
		void ShutDown();
		void BeginFrame();
		void EndFrame();
	};
}

