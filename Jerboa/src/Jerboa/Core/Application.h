#pragma once

namespace Jerboa {
    class Application
    {
    public:
        void Run();

        virtual void OnStart() {}
        virtual void OnShutdown() {}
    private:
        bool m_Running = true;
    };

    // Implemented by client
    Application* CreateApplication();
};