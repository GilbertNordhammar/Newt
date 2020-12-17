#include "jerboa-pch.h"
#include "LayerStack.h"

namespace Jerboa {
	LayerStack::~LayerStack() {
		for (auto* layer : mStack) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		mStack.emplace(mStack.begin() + mLayerInsertIndex, layer);
		mLayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		mStack.emplace_back(overlay);
	}

	void LayerStack::RemoveLayer(Layer* layer) {
		auto it = std::find(mStack.begin(), mStack.end(), layer);
		if (it != mStack.end())
		{
			mStack.erase(it);
			mLayerInsertIndex--;
		}
	}

	void LayerStack::RemoveOverlay(Layer* overlay) {
		auto it = std::find(mStack.begin(), mStack.end(), overlay);
		if (it != mStack.end())
			mStack.erase(it);
	}
}