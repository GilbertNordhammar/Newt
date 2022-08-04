#include "jerboa-pch.h"
#include "EventObserver.h"

namespace Jerboa {
    EventObserver::EventObserver(EventBus* eventBus, EventCallback callback, std::type_index eventIndex)
        : mEventBus(eventBus), mCallback(callback), mEventIndex(eventIndex) {
        Subscribe(mCallback, mEventIndex);
    }

    EventObserver::~EventObserver() {
        Unsubscribe(mCallback, mEventIndex);
    }

    void EventObserver::Subscribe(EventCallback& callback, std::type_index id) {
        mEventBus->Subscribe(callback, id);
    }

    void EventObserver::Unsubscribe(EventCallback& callback, std::type_index id) {
        mEventBus->Unsubscribe(callback, id);
    }
}