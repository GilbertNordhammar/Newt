#pragma once

#include "EventBus.h"

namespace Jerboa {
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = 0 {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		template<class EventType>
		void PublishInternalEvent(const EventType& evnt) {
			mInternalEventBus.Publish(evnt);
		}

		static EventBus* GetSharedEventBus() {
			static EventBus instance;
			return &instance;
		}

		inline const std::string& GetName() const { return mDebugName; }
	protected:
		EventBus mInternalEventBus;
		std::string mDebugName;
	};
}

