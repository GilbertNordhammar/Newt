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
            auto callbacks = m_Subscribers[GetTypeIndex<EventType>()];

            if (callbacks == nullptr) 
                return;

            for (auto& callback : *callbacks) {
                if (callback != nullptr) {
                    (*callback)(evnt);
                }
            }
        }

        template<class EventType>
        static constexpr EventIndex GetTypeIndex() {
            return std::type_index(typeid(EventType));
        }

    private:
        EventBus() {};

        static void Subscribe(EventCallback& callback, EventIndex id);
        static void Unsubscribe(EventCallback& callback, EventIndex id);

        static std::unordered_map<EventIndex, std::shared_ptr<CallbackList>> m_Subscribers;
    };
};