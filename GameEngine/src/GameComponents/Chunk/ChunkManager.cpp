#include "hzpch.h"
#include "ChunkManager.h"

namespace GameComponents {
	ChunkManager::ChunkManager()
	{
		this->chunks = new std::vector<
			std::vector<
				std::vector<
					GameEngine::Ref<Chunk>
				>
			>
		>();
		this->init();
	}

	void ChunkManager::init()
	{
		for (int x = 0; x < renderDistance; x++)
		{
			auto xList = std::vector<std::vector<GameEngine::Ref<Chunk>>>();
			this->chunks->push_back(xList);

			for (int y = 0; y < renderDistance; y++)
			{

				auto yList = std::vector<GameEngine::Ref<Chunk>>();
				this->chunks->at(x).push_back(yList);

				for (int z = 0; z < renderDistance; z++)
				{
					GameEngine::Ref<Chunk> t = GameEngine::CreateRef<Chunk>(glm::vec3({ x, y, z }));
					this->chunks->at(x).at(y).push_back(t);
				}
			}
		}
	}

	void ChunkManager::reload()
	{
		delete this->chunks;
		this->chunks = new std::vector<
			std::vector<
				std::vector<
					GameEngine::Ref<Chunk>
				>
			>
		>();

		this->init();
	}

	void ChunkManager::update()
	{
	}

	void ChunkManager::render()
	{
		for (auto const& x : *this->chunks) {
			for (auto const& y : x) {
				for (auto const& chunk : y) {
					chunk->render();
				}
			}
		}
	}
}