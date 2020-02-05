#pragma once

#include "GameEngine/Core/Core.h"
#include "GameEngine/Core/Layer/Layer.h"

namespace GameEngine {

	/*!
		Manage Layers and overlays.
	*/
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return this->layers.begin(); }
		std::vector<Layer*>::iterator end() { return this->layers.end(); }
	private:
		/*!
		contain list of layers and after all layers the overlays
		[layers, ..., layerInsert, overlays, ...]
		*/
		std::vector<Layer*> layers;
		unsigned int layerInsertIndex = 0;
	};
}

