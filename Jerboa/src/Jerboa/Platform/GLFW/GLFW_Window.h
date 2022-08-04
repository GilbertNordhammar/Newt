#pragma once

#include "Jerboa/Core/Window.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h" // OpenGL needs to be included before GLFW
#include "GLFW/glfw3.h"

namespace Jerboa 
{
	class GLFW_Window : public Window
	{
	public:
		GLFW_Window(const WindowProps& props);
		~GLFW_Window();

		virtual void Update() override;

		virtual int GetWidth() const override { return mData.width; };
		virtual int GetHeight() const override { return mData.height; };
		virtual glm::ivec2 GetPosition() const override;

		virtual CursorMode GetCursorMode() override { return mData.cursorMode; }
		virtual void SetCursorMode(CursorMode mode) override;

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return mData.VSync; };

		virtual void* GetNativeWindow() const { return mWindow; }
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

		GLFWwindow* mWindow;
		WindowData mData;
	};
}
