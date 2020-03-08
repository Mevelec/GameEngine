#pragma once

#include "GameComponents/Blocks/Block.h"
#include <map>

#include "GameEngine/Renderer/Geometry/Loader.h"


namespace GameComponents
{
	class BlockManager
	{
	public:
		GameEngine::Ref<Block> getBlock(BlockType type, BlockState state);
		const std::unordered_map<BlockState, GameEngine::Ref<Block>>& getBlockStates(BlockType type);

	private :
		GameEngine::Ref<Block> createBlock(BlockType type, BlockState state);

	private:
		std::unordered_map<BlockType, std::unordered_map<BlockState, GameEngine::Ref<Block>>> blocks;


	// Singleton + constructor
	public:
		static BlockManager& getInstance()
		{
			static BlockManager    instance;
			return instance;
		}
	private:
		BlockManager() {

			std::vector < glm::vec3 > out_vertices;
			std::vector < glm::vec2 > out_uvs;
			std::vector < glm::vec3 > out_normals;
			std::vector < int > out_indices;

			bool a = GameEngine::Loader::loadOBJ("assets/Models/test.obj", out_vertices, out_uvs, out_normals, out_indices);
		}

	public:
		BlockManager(BlockManager const&) = delete;
		void operator=(BlockManager const&) = delete;

	};
}
