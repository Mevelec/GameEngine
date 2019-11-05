#include "hzpch.h"
#include "LayerStack.h"

namespace GameEngine {

	LayerStack::LayerStack() {
	}

	LayerStack::~LayerStack() {
		for (ILayer* layer : layers)
			delete layer;
	}

	void LayerStack::pushLayer(ILayer* layer) {
		this->layers.emplace(this->layers.begin() + this->layerInsertIndex, layer);
		this->layerInsertIndex++;
		layer->onAttach();
	}
	void LayerStack::pushOverlay(ILayer* overlay) {
		this->layers.emplace_back(overlay);
		overlay->onAttach();
	}
	void LayerStack::popLayer(ILayer* layer) {
		auto it = std::find(this->layers.begin(), this->layers.end(), layer);
		if ( it != this->layers.end()) {
			this->layers.erase(it);
			this->layerInsertIndex--;
			layer->onDetach();
		}
	}
	void LayerStack::popOverlay(ILayer* overlay) {
		auto it = std::find(this->layers.begin(), this->layers.end(), overlay);
		if (it != this->layers.end()) {
			this->layers.erase(it);
			overlay->onDetach();
		}
	}
}