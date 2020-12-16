#include "jerboa-pch.h"
#include "Application.h"

namespace Jerboa {
    void Application::Run() {
        OnStart();
        while (mRunning) {
            // TODO
        }
        OnShutdown();
    }

    void Application::PushLayer(Layer* layer) {
        mLayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        mLayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
}