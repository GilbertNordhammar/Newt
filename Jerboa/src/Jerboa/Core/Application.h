#pragma once
#include "LayerStack.h"
#include "Window.h"
#include "EventObserver.h"
#include "Events/WindowResizeEvent.h"

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

        std::unique_ptr<Window> mWindow;
        bool mRunning = true;
        LayerStack mLayerStack;

        EventObserver mWindowResizeObserver;
    };

    // Implemented by client
    Application* CreateApplication();
};