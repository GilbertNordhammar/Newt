#pragma once

#include "EventBus.h"
#include <memory>

namespace Jerboa {

	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "Jerboa",
			unsigned int width = 1280,
			unsigned int height = 720)
			: title(title), width(width), height(height)
		{}
	};

	struct WindowPosition {
		float x, y;
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual WindowPosition GetPosition() const = 0;

		// Window attributes
		virtual std::weak_ptr<EventBus> GetEventBus() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}


