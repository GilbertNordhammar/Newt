#include "jerboa-pch.h"
#include "Application.h"

namespace Jerboa {
    void Application::Run() {
        OnStart();
        while (m_Running) {
            // TODO
        }
        OnShutdown();
    }
}