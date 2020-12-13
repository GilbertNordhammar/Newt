#include "jerboa-pch.h"
#include "EventBus.h"

namespace Jerboa {
    void EventBus::Subscribe(EventCallback& callback, std::type_index id) {
        auto callbacks = mSubscribers[id];

        if (callbacks == nullptr) {
            callbacks = std::make_shared<CallbackList>();
            mSubscribers[id] = callbacks;
        }

        callbacks->push_back(&callback);
    }

    void EventBus::Unsubscribe(EventCallback& callback, std::type_index id) {
        auto callbacks = mSubscribers[id];

        if (callbacks == nullptr) {
            return;
        }

        callbacks->remove(&callback);
    }
}