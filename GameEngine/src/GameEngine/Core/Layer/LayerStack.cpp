#include "hzpch.h"
#include "GameEngine/Core/Layer/LayerStack.h"

namespace GameEngine {

	LayerStack::~LayerStack() {
		for (Layer* layer : layers)
		{
			layer->onDetach();
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		this->layers.emplace(this->layers.begin() + this->layerInsertIndex, layer);
		this->layerInsertIndex++;
	}
	void LayerStack::pushOverlay(Layer* overlay) {
		this->layers.emplace_back(overlay);
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
		if (it != this->layers.begin() + this->layerInsertIndex) {
			this->layers.erase(it);
			overlay->onDetach();
		}
	}
}