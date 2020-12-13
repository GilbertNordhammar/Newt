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
    class EventObserverBase;
    
    typedef std::function<void(const Event&)> EventCallback;

    class EventBus {
        friend class Jerboa::EventObserverBase;

        typedef std::list<EventCallback*> CallbackList;
    
    public:
        template<class EventType>
        void Publish(const EventType& evnt) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            auto callbacks = mSubscribers[typeid(EventType)];

            if (callbacks == nullptr) {
                return;
            }

            for (auto& callback : *callbacks) {
                if (callback != nullptr) {
                    (*callback)(evnt);
                }
            }
        }

        static EventBus* Get() {
            static EventBus instance;
            return &instance;
        }

    private:
        void Subscribe(EventCallback& callback, std::type_index id);
        void Unsubscribe(EventCallback& callback, std::type_index id);

        std::unordered_map<std::type_index, std::shared_ptr<CallbackList>> mSubscribers;
    };
};