#pragma once

#include "Event.h"
#include <typeinfo>
#include <typeindex>
#include <map>
#include <unordered_map>
#include <type_traits>

namespace Jerboa {
    class EventObserverBase;

    class HandlerFunctionBase {
    public:
        void exec(Event* evnt) {
            call(evnt);
        }
    private:
        virtual void call(Event* evnt) = 0;
    };

    template<class T, class EventType>
    class MemberFunctionHandler : public HandlerFunctionBase
    {
    public:
        typedef void (T::* MemberFunction)(EventType*);

        MemberFunctionHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};

        void call(Event* evnt) {
            // Cast event to the correct type and call member function
            (instance->*memberFunction)(static_cast<EventType*>(evnt));
        }

        // Pointer to class instance
        T* instance;

        // Pointer to member function
        MemberFunction memberFunction;
        
    };

    typedef std::list<HandlerFunctionBase*> HandlerList;
    class EventBus {
    public:
        template<class EventType>
        void Publish(EventType* evnt) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            HandlerList* handlers = mSubscribers[typeid(EventType)];

            if (handlers == nullptr) {
                return;
            }

            for (auto& handler : *handlers) {
                if (handler != nullptr) {
                    handler->exec(evnt);
                }
            }
        }

    private:
        std::unordered_map<std::type_index, HandlerList*> mSubscribers;

        template<class T, class EventType>
        void Subscribe(T* instance, void (T::* memberFunction)(EventType*)) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            HandlerList* handlers = mSubscribers[typeid(EventType)];

            //First time initialization
            if (handlers == nullptr) {
                handlers = new HandlerList();
                mSubscribers[typeid(EventType)] = handlers;
            }

            handlers->push_back(new MemberFunctionHandler(instance, memberFunction));
        }

        template<class EventType, class T>
        void Unsubscribe(T* instance) {
            static_assert(std::is_base_of<Event, EventType>::value, "EventType must inherit from Event");

            HandlerList* handlers = mSubscribers[typeid(EventType)];

            if (handlers == nullptr) {
                return;
            }

            //handlers->remove_if([](MemberFunctionHandler<T, EventType> elem) { instance == elem.instance });
        }

        friend class Jerboa::EventObserverBase;
    };

    class EventObserverBase {
    public:
        EventObserverBase(EventBus* eventBus) : mEventBus(eventBus) {}

    protected:
        template<class T, class EventType>
        void Subscribe(T* instance, void (T::* memberFunction)(EventType*)) {
            mEventBus->Subscribe(instance, memberFunction);
        }

        template<class T, class EventType>
        void Unsubscribe(T* instance, void (T::* memberFunction)(EventType*)) {
            mEventBus->Unsubscribe<EventType>(instance);
        }

    private:

        EventBus* mEventBus;
    };

    template<class T, class EventType>
    class EventObserver : EventObserverBase {
    public:
        typedef void (T::* MemberFunction)(EventType*);

        EventObserver(EventBus* eventBus): 
            EventObserverBase(eventBus)
        {
            JERBOA_LOG_INFO("Creating EventObserver");
        }

        ~EventObserver() {
            if (mInstance) {
                JERBOA_LOG_INFO("Unsubscribing");
                Unsubscribe(mInstance, mMemberFunction);
            }
            JERBOA_LOG_INFO("Destroying EventObserver");
        }

        void OnEvent(T* instance, MemberFunction memberFunction) {
            JERBOA_LOG_INFO("Subscribing");
            mInstance = instance;
            mMemberFunction = memberFunction;
            Subscribe(instance, memberFunction);
        }

    private:
        T* mInstance;
        MemberFunction mMemberFunction;
    };
};