#include "hzpch.h"
#include "Block.h"

#include "GameEngine/Renderer/Renderer.h"

namespace GameComponents {

	bool operator==(const BlockState& lhs, const BlockState& rhs){
		if (lhs.visible == rhs.visible)
			return true;
		return false;
	}
}