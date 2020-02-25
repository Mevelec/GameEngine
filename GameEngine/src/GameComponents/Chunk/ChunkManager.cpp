#include "hzpch.h"
#include "ChunkManager.h"

namespace GameComponents {
	ChunkManager::ChunkManager()
	{
		GameEngine::Ref<Chunk> t = GameEngine::CreateRef<Chunk>();

		std::vector<GameEngine::Ref<Chunk>> a;
		a.push_back(t);

		std::vector<std::vector<GameEngine::Ref<Chunk>>> b;
		b.push_back(a);
		this->chunks.push_back(b);
	}
	void ChunkManager::update()
	{
	}
	void ChunkManager::render()
	{
		for (auto const& x : this->chunks) {
			for (auto const& y : x) {
				for (auto const& chunk : y) {
					chunk->render();
				}
			}
		}
	}
}