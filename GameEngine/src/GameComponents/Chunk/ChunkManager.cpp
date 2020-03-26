#include "hzpch.h"
#include "ChunkManager.h"

namespace GameComponents {
	ChunkManager::ChunkManager()
	{
		GE_PROFILE_FUNCTION();
		this->chunks = std::list<Chunk>();

		this->init();
	}


	void ChunkManager::init()
	{
		GE_PROFILE_FUNCTION();
		for (int i = 0; i < this->renderDistance; i++)
		{
			this->chunks.push_back(Chunk({i, 0, 0}));
		}
	}

	void ChunkManager::reload()
	{
		GE_PROFILE_FUNCTION();
		/*
		delete this->chunks;
		this->chunks = new std::vector<
			std::vector<
				std::vector<
					GameEngine::Ref<Chunk>
				>
			>
		>();*/

		this->init();
	}

	void ChunkManager::update()
	{
		GE_PROFILE_FUNCTION();

	}

	void ChunkManager::render()
	{
		GE_PROFILE_FUNCTION();

		for (std::list<Chunk>::iterator it = this->chunks.begin(); it != this->chunks.end(); it++)
		{
			it->render();
			/*
			for (auto const& y : x) {
				for (auto const& chunk : y) {
					chunk->render();
				}
			}*/
		}
	}
}