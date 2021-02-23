#pragma once

#include <vector>
#include <list>

#include"GameComponents/Chunk/Chunk.h"
#include"GameComponents/Chunk/ChunkEvent.h"

namespace GameComponents {
	class ChunkManager : public GameEngine::EventHandler
	{
	public:
		ChunkManager(glm::uvec3 pos = { 0, 0, 0 });

		void update();
		void render();
		void reload();
		bool load();


	public :
		virtual void onEvent(GameEngine::Event& e) override;
		bool onChunkDoReload(GameEngine::ChunkDoReloadEvent& event);
		bool onChunkSetRenderView(GameEngine::ChunkSetRenderViewEvent& event);
		bool onChunkMoveCenter(GameEngine::ChunkMoveCenterEvent& event);

	public:
		uint32_t getChunkSize() { return pow(2, this->chunkDepth); }

		void setRenderDistance(uint32_t distance) { this->renderDistance = distance; }
		const uint32_t& getRenderDistance() { return this->renderDistance; }

		const glm::uvec3& getCenter() { return this->center; }
	private:
		void init();

	private:
		std::list<Chunk> chunks;
		glm::uvec3 center;

		uint32_t renderDistance = 2;
		uint32_t chunkDepth = 4;

	};
}

