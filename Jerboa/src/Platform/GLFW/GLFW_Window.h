#pragma once

#include "Jerboa/Core/Window.h"

#define GLFW_INCLUDE_NONE // glad throws a compiler error without this being defined
#include "GLFW/glfw3.h"

namespace Jerboa 
{
	using NativeGLFWWindow = GLFWwindow;

	class GLFW_Window : public Window
	{
	public:
		GLFW_Window(const WindowProps& props);
		~GLFW_Window();

		virtual void Update() override;
		virtual void Clear() override;

		virtual int GetWidth() const override { return mData.width; };
		virtual int GetHeight() const override { return mData.height; };
		virtual WindowPosition GetPosition() const override;
		virtual std::weak_ptr<EventBus> GetEventBus() override { return mData.eventBus; };

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return mData.VSync; };

		virtual void* GetNativeWindow() const { return mWindow; }
	private:
		struct WindowData
		{
			std::string title;
			int width, height;
			bool VSync;

			std::shared_ptr<EventBus> eventBus = std::make_shared<EventBus>();
		};

		void Init(const WindowProps& props);
		void ShutDown();

		NativeGLFWWindow* mWindow;
		WindowData mData;
	};
}
