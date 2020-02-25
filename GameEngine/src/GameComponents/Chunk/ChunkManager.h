#pragma once

#include <vector>

#include"GameComponents/Chunk/Chunk.h"

namespace GameComponents {
	class ChunkManager
	{
	public:
		ChunkManager();
		void update();
		void render();
	private:
		std::vector<std::vector<std::vector<GameEngine::Ref<Chunk>>>> chunks;
	};
}

