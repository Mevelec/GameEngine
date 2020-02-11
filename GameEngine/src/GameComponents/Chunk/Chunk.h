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
		bool generateVA();
	private:
		GameEngine::Scope<OcTree::Octree<BlockType>> chunk;

		GameEngine::Ref<GameEngine::VertexArray> VA;

		GameEngine::ShaderLibrary shaderLib;
		GameEngine::MaterialLibrary materialLib;
	};
}

