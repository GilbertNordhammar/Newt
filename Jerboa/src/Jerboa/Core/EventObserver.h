#pragma once
#include "EventBus.h"
#include "EventObserverBase.h"

namespace Jerboa {

    class EventObserver : EventObserverBase {
    public:
        template<class EventType, class T>
        static EventObserver Create(EventBus* eventBus, T* instance, void (T::* memberFunction)(const EventType&) ) {
            return EventObserver(
                eventBus,
                [=](const Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); },
                EventBus::GetTypeIndex<EventType>()
            );
        }

        ~EventObserver();

    private:
        EventObserver(EventBus* eventBus, EventCallback callback, std::type_index eventIndex);

        EventCallback mCallback;
        std::type_index mEventIndex;
    };
}

