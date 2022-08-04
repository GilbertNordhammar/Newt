#include "jerboa-pch.h"
#include "EventObserver.h"

namespace Jerboa {
    EventObserver::~EventObserver()
    {
        UnsubscribeAll();
    }

    void EventObserver::UnsubscribeAll()
    {
        for (auto& it : m_Callbacks)
        {
            EventIndex eventIndex = it.first;
            EventCallback& callback = it.second;
            EventBus::Unsubscribe(callback, eventIndex);
        }
        m_Callbacks.clear();
    }
}