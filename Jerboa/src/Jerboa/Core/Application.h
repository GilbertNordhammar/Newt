#pragma once

#include "LayerStack.h"

#include "EventObserver.h"
#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/KeyRepeatEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"
#include "Events/MouseMovedEvent.h"
#include "Events/MouseScrolledEvent.h"
#include "Events/WindowCloseEvent.h"
#include "Events/WindowResizeEvent.h"
#include "Jerboa/Rendering/RenderState.h"
#include "Jerboa/Rendering/Renderer.h"
#include "Window.h"

namespace Jerboa
{
    struct ApplicationProps
    {
        WindowProps windowProps;
    };

    class Application
    {
    public:
                        Application(const ApplicationProps &props);
        virtual         ~Application() = 0;

        void            Run();

        void            PushLayer(Layer *layer);
        void            PushOverlay(Layer *overlay);

        Window&         GetWindow() { return *m_Window; }
        Renderer&       GetRenderer() { return *m_Renderer; }
        Renderer*       GetRendererPtr() { return m_Renderer; }
        bool            IsRunning() { return m_Running; }

    private:
        void            Init();
        void            ShutDown();

        void            RenderImGui();

        void            OnWindowClose(const WindowCloseEvent &evnt);
        void            OnWindowResize(const WindowResizeEvent& evnt);

        virtual void    OnInit() {}
        virtual void    OnShutdown() {}

        Window*         m_Window;
        bool            m_Running = true;
        LayerStack      m_LayerStack;
        Renderer*       m_Renderer;
        EventObserver   m_EventObserver;
    };

    // Implemented by client
    Application *CreateApplication();

}; // namespace Jerboa