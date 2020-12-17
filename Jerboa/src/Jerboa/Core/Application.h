#pragma once
#include "LayerStack.h"

namespace Jerboa {
    class Application
    {
    public:
        void Run();

        virtual void OnStart() {}
        virtual void OnShutdown() {}

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
    private:
        bool mRunning = true;
        LayerStack mLayerStack;
    };

    // Implemented by client
    Application* CreateApplication();
};