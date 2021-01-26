#pragma once
#include "LayerStack.h"

#include "glad/glad.h"

#include "Window.h"
#include "EventObserver.h"
#include "Events/WindowResizeEvent.h"
#include "Events/WindowCloseEvent.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/KeyRepeatEvent.h"
#include "Events/MouseMovedEvent.h"
#include "Events/MouseScrolledEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"

#include <memory>

namespace Jerboa {
    struct ApplicationProps {
        WindowProps windowProps;
    };

    class Application
    {
    public:
        Application(const ApplicationProps& props);

        void Run();

        virtual void OnInit() {}
        virtual void OnShutdown() {}

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        void Init();
        void ShutDown();

        void RenderImGui();

        void OnWindowResize(const WindowResizeEvent& evnt);
        void OnWindowClose(const WindowCloseEvent& evnt);
        void OnKeyPressed(const KeyPressedEvent& evnt);
        void OnKeyReleased(const KeyReleasedEvent& evnt);
        void OnKeyRepeat(const KeyRepeatEvent& evnt);
        void OnMouseMoved(const MouseMovedEvent& evnt);
        void OnMouseScrolled(const MouseScrolledEvent& evnt);
        void OnMouseButtonPressed(const MouseButtonPressedEvent& evnt);
        void OnMouseButtonReleased(const MouseButtonReleasedEvent& evnt);

        Window* mWindow;
        bool mRunning = true;
        LayerStack mLayerStack;

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
    Application* CreateApplication();
};