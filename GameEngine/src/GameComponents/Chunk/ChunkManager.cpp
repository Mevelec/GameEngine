#include "hzpch.h"
#include "ChunkManager.h"

namespace GameComponents {
	ChunkManager::ChunkManager(glm::uvec3 pos)
		: center(pos)
	{
		GE_PROFILE_FUNCTION();
		this->chunks = std::list<Chunk>();

		this->init();
	}


	void ChunkManager::init()
	{
		GE_PROFILE_FUNCTION();
		for (int i = this->renderDistance *-1; i < (int)this->renderDistance; i++)
		{
			this->chunks.push_back(Chunk(this->chunkDepth, {i, 0, 0}));
		}
	}

	bool ChunkManager::load() 
	{
			int i = 0;
			return false;
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


	// EVENTS //

	void ChunkManager::onEvent(GameEngine::Event& e)
	{
		GameEngine::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<GameEngine::ChunkDoReloadEvent>(GE_BIND_EVENT_FN(ChunkManager::onChunkDoReload));
		dispatcher.Dispatch<GameEngine::ChunkSetRenderViewEvent>(GE_BIND_EVENT_FN(ChunkManager::onChunkSetRenderView));
		dispatcher.Dispatch<GameEngine::ChunkMoveCenterEvent>(GE_BIND_EVENT_FN(ChunkManager::onChunkMoveCenter));

	}

	bool ChunkManager::onChunkDoReload(GameEngine::ChunkDoReloadEvent& event)
	{
		this->reload();
		return false;
	}

	bool ChunkManager::onChunkSetRenderView(GameEngine::ChunkSetRenderViewEvent& event)
	{
		this->setRenderDistance(event.GetValue());
		return false;
	}

	bool ChunkManager::onChunkMoveCenter(GameEngine::ChunkMoveCenterEvent& event)
	{
		auto a = event.GetValue();

		int xMove = a.x - this->center.x;
		if (abs(xMove) > this->renderDistance)
		{

		}
		else 
		{
			if (xMove > 0)
			{

			}
			else if(xMove < 0)
			{ }
			this->chunks.splice(destination, chunks, source);
		}

		this->center = a;
		return false;
	}
}

