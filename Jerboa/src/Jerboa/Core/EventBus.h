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
        typedef std::function<void(Event&)> CallbackFunc;
        typedef std::list<CallbackFunc*> CallbackFuncList;
    public:
        template<class EventType>
        void Publish(Event* evnt) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            CallbackFuncList* handlers = mSubscribers[typeid(EventType)];

            if (handlers == nullptr) {
                return;
            }

            for (auto& handler : *handlers) {
                if (handler != nullptr) {
                    (*handler)(*evnt);
                }
            }
        }

    private:
        template<class EventType>
        void Subscribe(CallbackFunc& callback) {
            CallbackFuncList* handlers = mSubscribers[typeid(EventType)];

            if (handlers == nullptr) {
                handlers = new CallbackFuncList();
                mSubscribers[typeid(EventType)] = handlers;
            }

            handlers->push_back(&callback);
        }

        template<class EventType>
        void Unsubscribe(CallbackFunc& callback) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            CallbackFuncList* handlers = mSubscribers[typeid(EventType)];

            if (handlers == nullptr) {
                return;
            }

            handlers->remove(&callback);
        }

        std::unordered_map<std::type_index, CallbackFuncList*> mSubscribers;

        friend class Jerboa::EventObserverBase;
    };

    class EventObserverBase {
    public:
        EventObserverBase(EventBus* eventBus) : mEventBus(eventBus) {}

    protected:
        template<class EventType>
        void Subscribe(std::function<void(Event& evnt)>& callback) {
            mEventBus->Subscribe<EventType>(callback);
        }

        template<class EventType>
        void Unsubscribe(std::function<void(Event& evnt)>& callback) {
            mEventBus->Unsubscribe<EventType>(callback);
        }

    private:

        EventBus* mEventBus;
    };

    template<class T, class EventType>
    class EventObserver : EventObserverBase {
    public:
        typedef void (T::* MemberFunction)(const EventType&);

        EventObserver(EventBus* eventBus): 
            EventObserverBase(eventBus)
        {
            JERBOA_LOG_INFO("Creating EventObserver");
        }

        ~EventObserver() {
            //if (mInstance) {
                JERBOA_LOG_INFO("Unsubscribing");
                Unsubscribe<EventType>(mCallback);
            //}
            JERBOA_LOG_INFO("Destroying EventObserver");
        }

        void OnEvent(T* instance, MemberFunction memberFunction) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");
            mCallback = [=](Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); };
            Subscribe<EventType>(mCallback);

            JERBOA_LOG_INFO("Subscribing");
        }

    private:
        std::function<void(Event& evnt)> mCallback;
    };
};