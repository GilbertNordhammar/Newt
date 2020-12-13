#pragma once
#include "EventBus.h"
#include "EventObserverBase.h"

namespace Jerboa {
    template<class T, class EventType>
    class EventObserver : EventObserverBase {
        typedef void (T::* MemberFunction)(const EventType&);

    public:
        EventObserver(EventBus* eventBus, T* instance, MemberFunction memberFunction)
            : EventObserverBase(eventBus)
        {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");
            
            mCallback = [=](const Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); };
            Subscribe(mCallback, std::type_index(typeid(EventType)));
        }

        ~EventObserver() {
            Unsubscribe(mCallback, std::type_index(typeid(EventType)));
        }

    private:
        EventCallback mCallback;
    };
}

