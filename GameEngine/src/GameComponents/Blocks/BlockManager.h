#pragma once

#include "GameComponents/Blocks/Block.h"
#include <map>

namespace GameComponents
{
	class BlockManager
	{
	public:
		GameEngine::Ref<Block> getBlock(BlockType type, BlockState state) {
			auto it = this->blocks.find(type);
			if (it != this->blocks.end())
			{
				auto it2 = it->second.find(state);
				if ( it2 != it->second.end())
				{
					return it2->second;
				}
				else
				{
					return this->createBlock(type, state);
				}
			}
			else
			{
				return this->createBlock(type, state);
			}
			return nullptr;
		}

	private :
		GameEngine::Ref<Block> createBlock(BlockType type, BlockState state) {
			GameEngine::Ref<Block> block = GameEngine::CreateRef<Block>(type, state);
			auto item = std::pair<BlockState, GameEngine::Ref<Block>>(state, block);

			auto it = this->blocks.find(type);
			if (it != this->blocks.end())
			{
				it->second.insert(item);
			}
			else
			{
				auto listStates = std::unordered_map<BlockState, GameEngine::Ref<Block> >();
				listStates.insert(item);
				auto blockTypeList = std::pair<BlockType, std::unordered_map<BlockState, GameEngine::Ref<Block>> >(type, listStates);
				this->blocks.insert(blockTypeList);
			}

			return block;
		}
	private:
		std::map<BlockType, std::unordered_map<BlockState, GameEngine::Ref<Block>>> blocks;


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
