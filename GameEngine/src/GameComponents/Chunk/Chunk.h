#pragma once

#include "GameComponents/Blocks/Block.h"
#include "OcTree/OcTree.h"
#include "GameEngine/Renderer/Renderable.h"

namespace GameComponents {

	class Chunk : public GameEngine::Renderable
	{
	public:
		Chunk();

		BlockType& get(int posx, int posy, int posz);
		void set(BlockType value, int posx, int posy, int posz);

		virtual void render() override;
	private:
		GameEngine::Scope<OcTree::Octree<BlockType>> chunk;
	};
}

