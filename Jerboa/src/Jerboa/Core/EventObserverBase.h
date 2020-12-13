#pragma once
#include "EventBus.h"

namespace Jerboa {
    class EventObserverBase {
    public:
        EventObserverBase(EventBus* eventBus) : mEventBus(eventBus) {}

    protected:
        void Subscribe(EventCallback& callback, std::type_index id) {
            mEventBus->Subscribe(callback, id);
        }

        void Unsubscribe(EventCallback& callback, std::type_index id) {
            mEventBus->Unsubscribe(callback, id);
        }

    private:

        EventBus* mEventBus;
    };
}
