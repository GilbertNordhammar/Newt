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
        m_Renderer(Renderer::Create())
    {
        m_EventObserver.Subscribe(this, &Application::OnWindowClose);
        m_Window->SetVSync(true);
    }

    Application::~Application()
    {
        delete m_Renderer;
        //delete m_Window;
    }

    void Application::Run() {
        Init();

        while (m_Running) {
            OPTICK_FRAME("MainThread");
            m_Renderer->Clear();

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
        m_Renderer->GetStatePtr()->ResetStateToDefaultValues();

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

    void Application::OnWindowClose(const WindowCloseEvent& evnt)
    {
        m_Running = false;
    }
}