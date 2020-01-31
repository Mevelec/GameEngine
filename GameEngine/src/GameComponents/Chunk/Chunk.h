#pragma once

#include "GameComponents/Blocks/Block.h"

namespace GameComponents {
	class Chunk
	{
		BlockType getBlock(glm::vec3 pos);
		BlockType setBlock(glm::vec3 pos);
	};
}

