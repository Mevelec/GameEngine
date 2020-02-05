#include "hzpch.h"

#include "OcTree/SVO/OcTreeDefault.h"

#include "Chunk.h"

namespace GameComponents {
	Chunk::Chunk()
	{
		this->chunk = GameEngine::CreateScope<OcTree::OcTreeDefault<BlockType>>(2);

		for (int x = 0; x <= chunk->getWidth() - 1; x++)
		{
			for (int z = 0; z <= chunk->getWidth() - 1; z++)
			{
				for (int y = 0; y <= chunk->getWidth() - 1; y++)
				{
					if (y > chunk->getWidth() - 2)
						chunk->set(GameComponents::BlockType::Grass, x, y, z);
					else
						chunk->set(GameComponents::BlockType::Dirt, x, y, z);
				}
			}
		}
		chunk->set(GameComponents::BlockType::Stone, 0, 0, 0);
//ocTree->setNode(Blocks::BlockType::Stone, 9, 9, 0, 1);
//ocTree->setNode(Blocks::BlockType::Dirt, 10, 10, 0, 1);
	}

	BlockType& Chunk::get(int posx, int posy, int posz) {
		return this->chunk->get(posx, posy, posz);
	};
	void Chunk::set(BlockType value, int posx, int posy, int posz) {
		this->chunk->set(value, posx, posy, posz);
	};

	void Chunk::render()
	{
		for (int x = 0; x <= chunk->getWidth() - 1; x++)
		{
			for (int z = 0; z <= chunk->getWidth() - 1; z++)
			{
				for (int y = 0; y <= chunk->getWidth() - 1; y++)
				{
					GameComponents::BlockRegistery::getInstance().renderBlock(chunk->get(x, y, z), glm::vec3(x * 2, y * 2, z * 2));
				}
			}
		}
	}
}