#pragma once

#include <vector>
#include <list>

#include"GameComponents/Chunk/Chunk.h"

namespace GameComponents {
	class ChunkManager
	{
	public:
		ChunkManager();
		void update();
		void render();
		void reload();

		void setRenderDistance(uint32_t distance) { this->renderDistance = distance; }
		uint32_t getRenderDistance() { this->renderDistance; }
	private:
		void init();

	private:
		std::list<Chunk> chunks;

		uint32_t renderDistance = 5;

	};
}

