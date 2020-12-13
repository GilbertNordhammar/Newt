#pragma once

#include "EventBus.h"

namespace Jerboa {
	enum class EventScope {
		Internal, Global
	};

	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = 0 {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		template<class EventType>
		void PublishEvent(EventType evnt, EventScope scope) {
			if (scope == EventScope.Internal)
				mEventBus.Publish(evnt);
			else
				EventBus::Get()->Publish(evnt);
		}

		inline const std::string& GetName() const { return mDebugName; }
	protected:
		EventBus mEventBus;
		std::string mDebugName;
	};
}

