#pragma once

#include "Layer.h"
#include <vector>
#include <memory>

namespace Jerboa {
	class LayerStack
	{
	public:
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void RemoveLayer(Layer* layer);
		void RemoveOverlay(Layer* overlay);

		const std::vector<Layer*>& GetStack() const { return mStack; }
		std::vector<Layer*>::iterator begin() { return mStack.begin(); }
		std::vector<Layer*>::iterator end() { return mStack.end(); }
	private:
		std::vector<Layer*> mStack;
		unsigned int mLayerInsertIndex = 0;
	};
}

