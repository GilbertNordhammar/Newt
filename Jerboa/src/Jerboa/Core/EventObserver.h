#pragma once
#include "EventBus.h"

namespace Jerboa {
    class EventObserver 
    {
    public:
        template<class EventType, class T>
        static EventObserver Create(EventBus* eventBus, T* instance, void (T::* memberFunction)(const EventType&) ) {
            return EventObserver(
                eventBus,
                [=](const Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); },
                EventBus::GetTypeIndex<EventType>()
            );
        }

        
        template<class EventType, class T>
        static std::unique_ptr<EventObserver> CreatePtr(EventBus* eventBus, T* instance, void (T::* memberFunction)(const EventType&)) {
            return std::unique_ptr<EventObserver>( // Not as safe as std::make_unique, but then the constructor would need to be public
                new EventObserver(
                    eventBus,
                    [=](const Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); },
                    EventBus::GetTypeIndex<EventType>()
                )
            );
        }

        void Subscribe(EventCallback& callback, std::type_index id);
        void Unsubscribe(EventCallback& callback, std::type_index id);
        
        ~EventObserver();

    private:
        EventObserver(EventBus* eventBus, EventCallback callback, std::type_index eventIndex);

        EventCallback mCallback;
        std::type_index mEventIndex;
        EventBus* mEventBus;
    };
}

