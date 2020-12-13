#pragma once

#include <typeinfo>
#include <typeindex>
#include <map>
#include <unordered_map>
#include <type_traits>
#include <memory>
#include <functional>

namespace Jerboa {
    class Event {};
    class EventObserverBase;
    
    typedef std::function<void(const Event&)> EventCallback;

    class EventBus {
        typedef std::list<EventCallback*> CallbackList;
    public:
        template<class EventType>
        void Publish(const EventType& evnt) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            auto callbacks = mSubscribers[typeid(EventType)];

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
        void Subscribe(EventCallback& callback, std::type_index id) {
            auto callbacks = mSubscribers[id];
            
            if (callbacks == nullptr) {
                callbacks = std::make_shared<CallbackList>();
                mSubscribers[id] = callbacks;
            }

            callbacks->push_back(&callback);
        }

        void Unsubscribe(EventCallback& callback, std::type_index id) {
            auto callbacks = mSubscribers[id];

            if (callbacks == nullptr) {
                return;
            }

            callbacks->remove(&callback);
        }

        std::unordered_map<std::type_index, std::shared_ptr<CallbackList>> mSubscribers;

        friend class Jerboa::EventObserverBase;
    };

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

    template<class T, class EventType>
    class EventObserver : EventObserverBase {
    public:
        typedef void (T::* MemberFunction)(const EventType&);

        EventObserver(EventBus* eventBus, T* instance, MemberFunction memberFunction)
            : EventObserverBase(eventBus)
        {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");
            mCallback = [=](const Event& evnt) { (instance->*memberFunction)(static_cast<const EventType&>(evnt)); };
            Subscribe(mCallback, std::type_index(typeid(EventType)));
            JERBOA_LOG_INFO("Creating EventObserver");
        }

        ~EventObserver() {
            Unsubscribe(mCallback, std::type_index(typeid(EventType)));
            JERBOA_LOG_INFO("Destroying EventObserver");
        }

    private:
        EventCallback mCallback;
    };
};