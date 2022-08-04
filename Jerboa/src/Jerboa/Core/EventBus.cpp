#include "jerboa-pch.h"
#include "EventBus.h"

namespace Jerboa {
    std::unordered_map<EventIndex, std::shared_ptr<CallbackList>> EventBus::m_Subscribers = {};

    void EventBus::Subscribe(EventCallback& callback, EventIndex id) {
        std::shared_ptr<CallbackList> callbacks = m_Subscribers[id];
        
        if (callbacks == nullptr) 
        {
            callbacks = std::make_shared<CallbackList>();
            m_Subscribers[id] = callbacks;
        }

        callbacks->push_back(&callback);
    }
    
    void EventBus::Unsubscribe(EventCallback& callback, EventIndex id) {
        auto callbacks = m_Subscribers[id];

        if (callbacks == nullptr)
            return;

        callbacks->remove(&callback);
    }
}