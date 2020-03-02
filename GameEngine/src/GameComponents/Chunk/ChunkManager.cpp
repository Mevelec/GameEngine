#include "hzpch.h"
#include "ChunkManager.h"

namespace GameComponents {
	ChunkManager::ChunkManager()
	{
		GameEngine::Ref<Chunk> t0 = GameEngine::CreateRef<Chunk>(glm::vec3({0, 0, 0}));
		GameEngine::Ref<Chunk> t1 = GameEngine::CreateRef<Chunk>(glm::vec3({ 0, 0, 1 }));
		GameEngine::Ref<Chunk> t2 = GameEngine::CreateRef<Chunk>(glm::vec3({ 0, 0, 2 }));
		GameEngine::Ref<Chunk> t3 = GameEngine::CreateRef<Chunk>(glm::vec3({ 0, 0, 3 }));

		std::vector<GameEngine::Ref<Chunk>> a;
		a.push_back(t0);
		/*a.push_back(t1);
		a.push_back(t2);
		a.push_back(t3);*/

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