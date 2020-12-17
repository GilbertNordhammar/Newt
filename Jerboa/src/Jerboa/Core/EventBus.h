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
            auto callbacks = mSubscribers[GetTypeIndex<EventType>()];

            if (callbacks == nullptr) {
                return;
            }

            for (auto& callback : *callbacks) {
                if (callback != nullptr) {
                    (*callback)(evnt);
                }
            }
        }

        template<class EventType>
        static std::type_index GetTypeIndex() {
            return std::type_index(typeid(EventType));
        }

    private:
        void Subscribe(EventCallback& callback, std::type_index id);
        void Unsubscribe(EventCallback& callback, std::type_index id);

        std::unordered_map<std::type_index, std::shared_ptr<CallbackList>> mSubscribers;
    };
};