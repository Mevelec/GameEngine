#pragma once

#include <glm/glm.hpp>

#include "GameComponents/Blocks/Block.h"
#include "OcTree/OcTree.h"
#include "GameEngine/Renderer/Renderable.h"

namespace GameComponents {

	class Chunk : public GameEngine::Renderable
	{
	public:
		Chunk(const glm::vec3& position);

		BlockType& get(int posx, int posy, int posz);
		void set(BlockType value, int posx, int posy, int posz);

		inline const glm::vec3& getPostion() const { return this->position; }

		virtual void render() override;
	private:
		bool generateVA();
	private:
		glm::uvec3 position;

		GameEngine::Scope<OcTree::Octree<BlockType>> chunk;
		GameEngine::Scope<GameEngine::Geometry> cube;
		GameEngine::Ref<GameEngine::VertexArray> VA;

		GameEngine::ShaderLibrary shaderLib;
		GameEngine::MaterialLibrary materialLib;
	};
}

