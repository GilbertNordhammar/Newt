#pragma once

#include "glm/vec2.hpp"

#include <memory>

namespace Jerboa {
	class Renderer;

	enum class WindowApi 
	{
		None, GLFW
	};

	enum class CursorMode 
	{
		Normal, Disabled, Hidden
	};

	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;
		CursorMode cursorMode = CursorMode::Normal;

		WindowProps(
			const std::string& title = "Jerboa",
			unsigned int width = 1280,
			unsigned int height = 720)
			: title(title), width(width), height(height)
		{}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		virtual ~Window() {}

		virtual void Update() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual glm::ivec2 GetPosition() const = 0;
		virtual void* GetNativeWindow() const = 0;

		virtual CursorMode GetCursorMode() = 0;
		virtual void SetCursorMode(CursorMode mode) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		float GetAspectRatio() const { return (float) GetWidth() / (float) GetHeight(); }

		static void SetApi(WindowApi api) { sm_WindowApi = api; }
		static WindowApi GetApi() { return sm_WindowApi; }

		static Window* Create(const WindowProps& props);
		static Window* Get();

	private:
		static std::shared_ptr<Window> sm_Window;
		static WindowApi sm_WindowApi;
		Renderer* m_Renderer;
	};
}


