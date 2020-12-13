#pragma once

#include "Event.h"
#include <typeinfo>
#include <typeindex>
#include <map>
#include <unordered_map>
#include <type_traits>

namespace Jerboa {
    class EventObserverBase;

    class EventBus {
        typedef std::function<void(const Event&)> Callback;
        typedef std::list<Callback*> CallbackList;
    public:
        template<class EventType>
        void Publish(const EventType& evnt) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            CallbackList* callbacks = mSubscribers[typeid(EventType)];

            if (callbacks == nullptr) {
                return;
            }

            for (auto& callback : *callbacks) {
                if (callback != nullptr) {
                    (*callback)(evnt);
                }
            }
        }

    private:
        template<class EventType>
        void Subscribe(Callback& callback) {
            CallbackList* callbacks = mSubscribers[typeid(EventType)];

            if (callbacks == nullptr) {
                callbacks = new CallbackList();
                mSubscribers[typeid(EventType)] = callbacks;
            }

            callbacks->push_back(&callback);
        }

        template<class EventType>
        void Unsubscribe(Callback& callback) {
            CallbackList* callbacks = mSubscribers[typeid(EventType)];

            if (callbacks == nullptr) {
                return;
            }

            callbacks->remove(&callback);
        }

        std::unordered_map<std::type_index, CallbackList*> mSubscribers;

        friend class Jerboa::EventObserverBase;
    };

    class EventObserverBase {
    public:
        EventObserverBase(EventBus* eventBus) : mEventBus(eventBus) {}

    protected:
        template<class EventType>
        void Subscribe(std::function<void(const Event& evnt)>& callback) {
            mEventBus->Subscribe<EventType>(callback);
        }

        template<class EventType>
        void Unsubscribe(std::function<void(const Event& evnt)>& callback) {
            mEventBus->Unsubscribe<EventType>(callback);
        }

    private:

        EventBus* mEventBus;
    };

    template<class T, class EventType>
    class EventObserver : EventObserverBase {
    public:
        typedef void (T::* MemberFunction)(const EventType&);

        EventObserver(EventBus* eventBus, T* instance, MemberFunction memberFunction):
            EventObserverBase(eventBus)
        {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");
            mCallback = [=](const Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); };
            Subscribe<EventType>(mCallback);
            JERBOA_LOG_INFO("Creating EventObserver");
        }

        ~EventObserver() {
            Unsubscribe<EventType>(mCallback);
            JERBOA_LOG_INFO("Destroying EventObserver");
        }

    private:
        std::function<void(const Event& evnt)> mCallback;
    };
};