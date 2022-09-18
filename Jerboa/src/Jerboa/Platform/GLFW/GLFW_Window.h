#pragma once

#include "Jerboa/Core/Window.h"

#if defined(JERBOA_RENDER_API_OPENGL)
	#include "Jerboa/Platform/OpenGL/OpenGL.h" // OpenGL needs to be included before GLFW
#endif
#include "GLFW/glfw3.h"

namespace Jerboa 
{
	class GLFW_Window : public Window
	{
	public:
		GLFW_Window(const WindowProps& props);
		~GLFW_Window();

		virtual void Update() override;

		virtual int GetWidth() const override { return m_WindowData.width; };
		virtual int GetHeight() const override { return m_WindowData.height; };
		virtual glm::ivec2 GetPosition() const override;

		virtual CursorMode GetCursorMode() override { return m_WindowData.cursorMode; }
		virtual void SetCursorMode(CursorMode mode) override;

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return m_WindowData.VSync; };

		virtual void* GetNativeWindow() const { return m_WindowGLFW; }
	private:
		struct WindowData
		{
			std::string title;
			int width, height;
			bool VSync;
			CursorMode cursorMode;
		};

		void Init(const WindowProps& props);
		void ShutDown();

		GLFWwindow* m_WindowGLFW;
		WindowData m_WindowData;
	};
}
