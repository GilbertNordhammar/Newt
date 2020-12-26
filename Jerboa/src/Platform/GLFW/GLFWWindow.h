#pragma once

#include "Jerboa/Core/Window.h"
#include "GLFW/glfw3.h"

namespace Jerboa 
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow(const WindowProps& props);

		virtual void OnUpdate() override;

		virtual int GetWidth() const override { return mData.width; };
		virtual int GetHeight() const override { return mData.height; };
		virtual WindowPosition GetPosition() const override;
		virtual std::weak_ptr<EventBus> GetEventBus() override { return mEventBus; };

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return mData.VSync; };

	private:
		struct WindowData
		{
			std::string title;
			int width, height;
			bool VSync;
		};

		void Init(const WindowProps& props);

		std::unique_ptr<GLFWWindow> mWindow;
		WindowData mData;
		std::shared_ptr<EventBus> mEventBus;
	};
}
