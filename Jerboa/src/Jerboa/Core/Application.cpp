#include "jerboa-pch.h"
#include "Application.h"

namespace Jerboa {
    Application::Application(const ApplicationProps& props)
        : mWindow(std::unique_ptr<Window>(Window::Create(props.windowProps))),
        mWindowResizeObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnWindowResize)),
        mWindowCloseObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnWindowClose)),
        mKeyPressedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnKeyPressed)),
        mKeyReleasedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnKeyReleased)),
        mKeyRepeatObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnKeyRepeat)),
        mMouseMovedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnMouseMoved)),
        mMouseScrolledObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnMouseScrolled))
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
        Layer::GetSharedEventBus()->Publish(evnt);
    }

    void Application::OnWindowClose(const WindowCloseEvent& evnt)
    {
        mRunning = false;
    }

    void Application::OnKeyPressed(const KeyPressedEvent& evnt)
    {
        JERBOA_LOG_TRACE("Pressed '{}' (mods {}), ", GetKeyName(evnt.key), evnt.modifiers);
    }

    void Application::OnKeyReleased(const KeyReleasedEvent& evnt)
    {
        JERBOA_LOG_TRACE("Released '{}' (mods {}), ", GetKeyName(evnt.key), evnt.modifiers);
    }

    void Application::OnKeyRepeat(const KeyRepeatEvent& evnt)
    {
        JERBOA_LOG_TRACE("Continiously pressing '{}' (mods {}), ", GetKeyName(evnt.key), evnt.modifiers);
    }

    void Application::OnMouseMoved(const MouseMovedEvent& evnt)
    {
        JERBOA_LOG_TRACE("Mouse moved ({}, {})", evnt.x, evnt.y);
    }

    void Application::OnMouseScrolled(const MouseScrolledEvent& evnt)
    {
        JERBOA_LOG_TRACE("Mouse scrolled ({}, {})", evnt.xOffset, evnt.yOffset);
    }
}