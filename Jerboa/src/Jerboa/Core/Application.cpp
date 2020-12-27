#include "jerboa-pch.h"
#include "Application.h"

namespace Jerboa {
    Application::Application(const ApplicationProps& props)
        : mWindow(std::unique_ptr<Window>(Window::Create(props.windowProps))),
        mWindowResizeObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnWindowResize)),
        mWindowCloseObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnWindowClose))
    {
        mWindow->SetVSync(true);
    }

    void Application::Run() {
        OnStart();
        while (mRunning) {
            mWindow->OnUpdate();
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

    void Application::OnWindowResize(const WindowResizeEvent& evnt)
    {
        JERBOA_LOG_TRACE("window resized to {}x{}", evnt.width, evnt.height);
    }
    void Application::OnWindowClose(const WindowCloseEvent& evnt)
    {
        mRunning = false;
    }
}