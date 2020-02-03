#pragma once

#include "GameComponents/Blocks/Block.h"
#include <OcTree.h>

namespace GameComponents {

	class Chunk : public OcTree::OcTreeDefault<BlockType>
	{
	};
}

