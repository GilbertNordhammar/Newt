#pragma once
#include "EventBus.h"

#include "Jerboa/Debug.h"
#include <string>

namespace Jerboa {
    class EventObserver 
    {
    public:
        template<class EventType, class T>
        void Subscribe(T* instance, void (T::* memberFunction)(const EventType&))
        {
            auto eventIndex = EventBus::GetTypeIndex<EventType>();
            m_Callbacks[eventIndex] = [=](const Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); };
            EventBus::Subscribe(
                m_Callbacks[eventIndex],
                eventIndex
            );
        }

        template<class EventType>
        void Unsubscribe()
        {
            auto eventIndex = EventBus::GetTypeIndex<EventType>();
            auto callbackIterator = m_Callbacks.find(eventIndex);
            bool isSubscribed = callbackIterator != m_Callbacks.end();
            JERBOA_ASSERT(isSubscribed, "Can't unsubscribe to event '" + std::string(typeid(EventType).name()) + "' since it's not being subscribed to in the first place.");
            if (isSubscribed)
            {
                EventBus::Unsubscribe(callbackIterator->second, eventIndex);
                m_Callbacks.erase(eventIndex);
            }
        }

        void UnsubscribeAll();
        
        ~EventObserver();

    private:
        std::unordered_map<EventIndex, EventCallback> m_Callbacks;
    };
}

