#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Layer/ILayer.h"

namespace GameEngine {

	/*!
		Manage Layers and overlays.
	*/
	class GE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(ILayer* layer);
		void pushOverlay(ILayer* overlay);
		void popLayer(ILayer* layer);
		void popOverlay(ILayer* overlay);

		std::vector<ILayer*>::iterator begin() { return this->layers.begin(); }
		std::vector<ILayer*>::iterator end() { return this->layers.end(); }
	private:
		/*!
		contain list of layers and after all layers the overlays
		[layers, ..., layerInsert, overlays, ...]
		*/
		std::vector<ILayer*> layers;
		unsigned int layerInsertIndex = 0;
	};
}

