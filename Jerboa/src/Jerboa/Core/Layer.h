#pragma once

#include <string>

namespace Jerboa {
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = 0 {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}

		const std::string& GetName() const { return mDebugName; }
	protected:
		std::string mDebugName;
	};
}

