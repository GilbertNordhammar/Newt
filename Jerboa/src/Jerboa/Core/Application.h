#pragma once

#define GLFW_INCLUDE_NONE // This needs to be defined as early as possible or glad will throw an error saying that opengl header is already included
#include "LayerStack.h"

#include "EventObserver.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/KeyRepeatEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"
#include "Events/MouseMovedEvent.h"
#include "Events/MouseScrolledEvent.h"
#include "Events/WindowCloseEvent.h"
#include "Events/WindowResizeEvent.h"
#include "Jerboa/Rendering/RenderState.h"
#include "Window.h"

#include "Jerboa/Platform/OpenGL/OpenGL.h"

namespace Jerboa
{
    struct ApplicationProps
    {
        WindowProps windowProps;
    };

    class Application
    {
    public:
        Application(const ApplicationProps &props);
        virtual ~Application() = 0;

        void Run();

        virtual void OnInit() {}
        virtual void OnShutdown() {}

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);

    private:
        void Init();
        void ShutDown();

        void RenderImGui();

        void OnWindowResize(const WindowResizeEvent &evnt);
        void OnWindowClose(const WindowCloseEvent &evnt);
        void OnKeyPressed(const KeyPressedEvent &evnt);
        void OnKeyReleased(const KeyReleasedEvent &evnt);
        void OnKeyRepeat(const KeyRepeatEvent &evnt);
        void OnMouseMoved(const MouseMovedEvent &evnt);
        void OnMouseScrolled(const MouseScrolledEvent &evnt);
        void OnMouseButtonPressed(const MouseButtonPressedEvent &evnt);
        void OnMouseButtonReleased(const MouseButtonReleasedEvent &evnt);

        Window *m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
        RenderState *m_RenderState;

        EventObserver
            mWindowResizeObserver,
            mWindowCloseObserver,
            mKeyPressedObserver,
            mKeyReleasedObserver,
            mKeyRepeatObserver,
            mMouseMovedObserver,
            mMouseScrolledObserver,
            mMouseButtonPressedObserver,
            mMouseButtonReleasedObserver;
    };

    // Implemented by client
    Application *CreateApplication();
}; // namespace Jerboa