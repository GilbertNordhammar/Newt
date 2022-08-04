#pragma once

#include "Event.h"
#include <typeinfo>
#include <typeindex>
#include <map>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <functional>

namespace Jerboa {
    class EventObserver;
    
    typedef std::function<void(const Event&)> EventCallback;
    typedef std::list<EventCallback*> CallbackList;
    typedef std::type_index EventIndex;

    class EventBus {
        friend class EventObserver;
    public:
        template<class EventType>
        static void Publish(const EventType& evnt) {
            auto callbacksIterator = m_Subscribers.find(GetTypeIndex<EventType>());

            if (callbacksIterator == m_Subscribers.end())
                return;
            
            std::shared_ptr<CallbackList> callbacks = callbacksIterator->second;
            for (auto& callback : *callbacks) 
            {
                if (callback != nullptr) 
                    (*callback)(evnt);
            }
        }

    private:
        EventBus() {};

        static void Subscribe(EventCallback& callback, EventIndex id);
        static void Unsubscribe(EventCallback& callback, EventIndex id);

        template<class EventType>
        static constexpr EventIndex GetTypeIndex() 
        {
            return std::type_index(typeid(EventType));
        }

        static std::unordered_map<EventIndex, std::shared_ptr<CallbackList>> m_Subscribers;
    };
};