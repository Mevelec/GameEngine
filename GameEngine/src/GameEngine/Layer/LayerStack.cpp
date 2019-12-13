#include "hzpch.h"
#include "LayerStack.h"

namespace GameEngine {

	LayerStack::LayerStack() {
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : layers)
			delete layer;
	}

	void LayerStack::pushLayer(Layer* layer) {
		this->layers.emplace(this->layers.begin() + this->layerInsertIndex, layer);
		this->layerInsertIndex++;
		layer->onAttach();
	}
	void LayerStack::pushOverlay(Layer* overlay) {
		this->layers.emplace_back(overlay);
		overlay->onAttach();
	}
	void LayerStack::popLayer(Layer* layer) {
		auto it = std::find(this->layers.begin(), this->layers.end(), layer);
		if ( it != this->layers.end()) {
			this->layers.erase(it);
			this->layerInsertIndex--;
			layer->onDetach();
		}
	}
	void LayerStack::popOverlay(Layer* overlay) {
		auto it = std::find(this->layers.begin(), this->layers.end(), overlay);
		if (it != this->layers.end()) {
			this->layers.erase(it);
			overlay->onDetach();
		}
	}
}