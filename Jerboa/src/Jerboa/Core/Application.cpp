#include "jerboa-pch.h"
#include "Application.h"

#include "Jerboa/UI/ImGui/ImGuiApp.h"


namespace Jerboa {
    Application::Application(const ApplicationProps& props)
        : mWindow(std::unique_ptr<Window>(Window::Create(props.windowProps))),
        mWindowResizeObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnWindowResize)),
        mWindowCloseObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnWindowClose)),
        mKeyPressedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnKeyPressed)),
        mKeyReleasedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnKeyReleased)),
        mKeyRepeatObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnKeyRepeat)),
        mMouseMovedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnMouseMoved)),
        mMouseScrolledObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnMouseScrolled)),
        mMouseButtonPressedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnMouseButtonPressed)),
        mMouseButtonReleasedObserver(EventObserver::Create(mWindow->GetEventBus().lock().get(), this, &Application::OnMouseButtonReleased))
    {
        mWindow->SetVSync(true);
    }

    void Application::Run() {
        Init();
        while (mRunning) {
            mWindow->Clear();

            for (Layer* layer : mLayerStack)
                layer->OnUpdate();

            mWindow->Update();
        }
        ShutDown();
    }

    void Application::Init()
    {
        JERBOA_LOG_INFO("Initializing application");
        UI::ImGuiApp::Initialize(mWindow.get());

        OnInit();
    }

    void Application::ShutDown()
    {
        JERBOA_LOG_INFO("Shutting down application");
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

    void Jerboa::Application::OnMouseButtonPressed(const MouseButtonPressedEvent& evnt)
    {
        JERBOA_LOG_TRACE("Pressed mouse button {} (modifiers {})", evnt.button, evnt.modifiers);
    }

    void Jerboa::Application::OnMouseButtonReleased(const MouseButtonReleasedEvent& evnt)
    {
        JERBOA_LOG_TRACE("Released mouse button {} (modifiers {})", evnt.button, evnt.modifiers);
    }
}