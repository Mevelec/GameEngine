#pragma once

#include <vector>
#include <list>

#include"GameComponents/Chunk/Chunk.h"
#include"GameComponents/Chunk/ChunkEvent.h"

namespace GameComponents {
	class ChunkManager : public GameEngine::EventHandler
	{
	public:
		ChunkManager();

		virtual void onEvent(GameEngine::Event& e) override;
		void update();
		void render();
		void reload();
		void load(glm::vec3 center);

		void setRenderDistance(uint32_t distance) { this->renderDistance = distance; }
		uint32_t getRenderDistance() { this->renderDistance; }
	private:
		void init();

	private:
		std::list<Chunk> chunks;

		uint32_t renderDistance = 3;

	};
}

