#include "jerboa-pch.h"
#include "Application.h"

#include "Jerboa/Core/Input.h"
#include "Jerboa/Core/Time.h"
#include "Jerboa/Platform/Platform.h"
#include "Jerboa/Rendering/Renderer.h"
#include "Jerboa/UI/ImGui/ImGuiApp.h"


#include "optick.h"

namespace Jerboa {
    Application::Application(const ApplicationProps& props)
        : m_Window(Window::Create(props.windowProps)),
        m_RenderState(RenderState::Create()),
        mWindowResizeObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnWindowResize)),
        mWindowCloseObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnWindowClose)),
        mKeyPressedObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnKeyPressed)),
        mKeyReleasedObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnKeyReleased)),
        mKeyRepeatObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnKeyRepeat)),
        mMouseMovedObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnMouseMoved)),
        mMouseScrolledObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnMouseScrolled)),
        mMouseButtonPressedObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnMouseButtonPressed)),
        mMouseButtonReleasedObserver(EventObserver::Create(m_Window->GetEventBus().lock().get(), this, &Application::OnMouseButtonReleased))
    {
        m_Window->SetVSync(true);
        
    }

    Application::~Application()
    {
        delete m_RenderState;
        //delete m_Window;
    }

    void Application::Run() {
        Init();

        while (m_Running) {
            OPTICK_FRAME("MainThread");
            Renderer::Clear();

            {
                OPTICK_EVENT("Update Layers");
                for (Layer* layer : m_LayerStack)
                    layer->OnUpdate();
            }

            RenderImGui();

            m_Window->Update();

            {
                OPTICK_EVENT("Update Time and Input");
                InputInternals::Update();
                TimeInternals::Update();
            }
        }
        ShutDown();
    }

    void Application::Init()
    {
        JERBOA_LOG_INFO("Initializing application...");
        
        Platform::SetRenderAPI(RenderAPI::OpenGL);
        InputInternals::Init();
        UI::ImGuiApp::Init(m_Window);
        m_RenderState->ResetStateToDefaultValues();

        OnInit();
    }

    void Application::ShutDown()
    {
        JERBOA_LOG_INFO("Shutting down application...");

        UI::ImGuiApp::ShutDown();

        OnShutdown();
    }

    void Application::RenderImGui()
    {
        OPTICK_EVENT("Application::RenderImGui()");
        Jerboa::UI::ImGuiApp::BeginFrame();
        
        for (Layer* layer : m_LayerStack)
            layer->OnImGuiRender();

        Jerboa::UI::ImGuiApp::EndFrame();
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnWindowResize(const WindowResizeEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
    }

    void Application::OnWindowClose(const WindowCloseEvent& evnt)
    {
        m_Running = false;
    }

    void Application::OnKeyPressed(const KeyPressedEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
        //JERBOA_LOG_TRACE("Pressed '{}' (mods {}), ", GetKeyName(evnt.key), evnt.modifiers);
    }

    void Application::OnKeyReleased(const KeyReleasedEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
        //JERBOA_LOG_TRACE("Released '{}' (mods {}), ", GetKeyName(evnt.key), evnt.modifiers);
    }

    void Application::OnKeyRepeat(const KeyRepeatEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
        //JERBOA_LOG_TRACE("Continiously pressing '{}' (mods {}), ", GetKeyName(evnt.key), evnt.modifiers);
    }

    void Application::OnMouseMoved(const MouseMovedEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
        //JERBOA_LOG_TRACE("Mouse moved ({}, {})", evnt.x, evnt.y);
    }

    void Application::OnMouseScrolled(const MouseScrolledEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
        //JERBOA_LOG_TRACE("Mouse scrolled ({}, {})", evnt.xOffset, evnt.yOffset);
    }

    void Jerboa::Application::OnMouseButtonPressed(const MouseButtonPressedEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
        //JERBOA_LOG_TRACE("Pressed mouse button {} (modifiers {})", evnt.button, evnt.modifiers);
    }

    void Jerboa::Application::OnMouseButtonReleased(const MouseButtonReleasedEvent& evnt)
    {
        Layer::GetSharedEventBus()->Publish(evnt);
        //JERBOA_LOG_TRACE("Released mouse button {} (modifiers {})", evnt.button, evnt.modifiers);
    }
}