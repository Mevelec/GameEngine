#include "hzpch.h"
#include "LayerStack.h"

namespace GameEngine {

	LayerStack::LayerStack() {
		this->layerInsert = layers.begin();
	}

	LayerStack::~LayerStack() {
		for (ILayer* layer : layers)
			delete layer;
	}

	void LayerStack::pushLayer(ILayer* layer) {
		this->layerInsert = this->layers.emplace(this->layerInsert, layer);
	}
	void LayerStack::pushOverlay(ILayer* overlay) {
		this->layers.emplace_back(overlay);
	}
	void LayerStack::popLayer(ILayer* layer) {
		auto it = std::find(this->layers.begin(), this->layers.end(), layer);
		if ( it != this->layers.end()) {
			this->layers.erase(it);
			this->layerInsert--;
		}
	}
	void LayerStack::popOverlay(ILayer* overlay) {
		auto it = std::find(this->layers.begin(), this->layers.end(), overlay);
		if (it != this->layers.end()) {
			this->layers.erase(it);
		}
	}
}