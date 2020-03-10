#pragma once

#include "GameComponents/Blocks/Block.h"
#include <map>

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
		}

	public:
		BlockManager(BlockManager const&) = delete;
		void operator=(BlockManager const&) = delete;
	};
}
