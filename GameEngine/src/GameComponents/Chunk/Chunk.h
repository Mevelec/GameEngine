#pragma once

#include <glm/glm.hpp>

#include "GameComponents/Blocks/BlockManager.h"

#include "OcTree/OcTree.h"
#include "GameEngine/Renderer/Renderable.h"

namespace GameComponents {

	class Chunk : public GameEngine::Renderable
	{
	public:
		Chunk(const uint32_t& depth = 6,  const glm::vec3& position = { 0, 0, 0 });

		GameEngine::Ref<Block> get(int posx, int posy, int posz, bool checkNeighboors);

		void set(GameEngine::Ref<Block> value, int posx, int posy, int posz);

		inline const glm::vec3& getPostion() const { return this->position; }

		virtual void render() override;
	private:
		void generate();
		void load();
		void build();
		void unload();
	private:
		glm::vec3 position;
		bool hidden = false;

		GameEngine::Scope<OcTree::Octree< GameEngine::Ref<Block> >> chunk;
		GameEngine::Scope<GameEngine::Geometry> cube;
		GameEngine::Ref<GameEngine::VertexArray> VA;
	};
}

