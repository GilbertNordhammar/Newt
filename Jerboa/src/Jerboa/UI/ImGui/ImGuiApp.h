#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Jerboa/Core/Window.h"
#include "Jerboa/Debug.h"

namespace Jerboa::UI {
	class ImGuiApp {
	public:
		static void Initialize(Window* window);
		static void BeginFrame();
		static void EndFrame();
	};
}

