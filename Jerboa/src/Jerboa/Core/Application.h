#pragma once
#include "LayerStack.h"
#include "Window.h"
#include "EventObserver.h"
#include "Events/WindowResizeEvent.h"
#include "Events/WindowCloseEvent.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/KeyRepeatEvent.h"
#include "Events/MouseMovedEvent.h"
#include "Events/MouseScrolledEvent.h"

namespace Jerboa {
    struct ApplicationProps {
        WindowProps windowProps;
    };

    class Application
    {
    public:
        Application(const ApplicationProps& props);

        void Run();

        virtual void OnStart() {}
        virtual void OnShutdown() {}

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        void OnWindowResize(const WindowResizeEvent& evnt);
        void OnWindowClose(const WindowCloseEvent& evnt);
        void OnKeyPressed(const KeyPressedEvent& evnt);
        void OnKeyReleased(const KeyReleasedEvent& evnt);
        void OnKeyRepeat(const KeyRepeatEvent& evnt);
        void OnMouseMoved(const MouseMovedEvent& evnt);
        void OnMouseScrolled(const MouseScrolledEvent& evnt);

        std::unique_ptr<Window> mWindow;
        bool mRunning = true;
        LayerStack mLayerStack;

        EventObserver 
            mWindowResizeObserver, 
            mWindowCloseObserver,
            mKeyPressedObserver,
            mKeyReleasedObserver,
            mKeyRepeatObserver,
            mMouseMovedObserver,
            mMouseScrolledObserver;
    };

    // Implemented by client
    Application* CreateApplication();
};