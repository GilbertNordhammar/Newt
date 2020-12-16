#include "jerboa-pch.h"
#include "EventObserver.h"

namespace Jerboa {
    EventObserver::EventObserver(EventBus* eventBus, EventCallback callback, std::type_index eventIndex)
        : EventObserverBase(eventBus), mCallback(callback), mEventIndex(eventIndex) {
        Subscribe(mCallback, mEventIndex);
    }

    EventObserver::~EventObserver() {
        Unsubscribe(mCallback, mEventIndex);
    }
}