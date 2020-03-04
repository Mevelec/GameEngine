#pragma once
#include "GameEngine/Renderer/Material/Shader.h"
#include "GameEngine/Renderer/Material/MaterialLibrary.h"
#include "GameEngine/Renderer/Geometry/Geometry.h"
#include "GameEngine/Renderer/Geometry/Primitives.h"

#include "GameEngine/Core/Transform/Transform.h"

#include <glm/gtc/type_ptr.hpp>
#include <functional>


namespace GameComponents{
	
	struct BlockState {
		bool visible;

		size_t operator()(void) const {}
		bool operator()(const BlockState& other) const {}
	};

	bool operator==(const BlockState& lhs, const BlockState& rhs);


	// custom specialization of std::hash can be injected in namespace std
	


	enum class BlockType {
		BlockType_Default = 0,

		Grass = 100,
		Dirt  = 200,
		Stone = 300
	};

	class Block
	{
	public:
		Block(BlockType blockType, BlockState state) { 
			this->blockType = blockType;
			this->state = state; 
		};
		~Block() {};

		inline const bool isVisible() const { return this->state.visible; };
		inline void setVisible(bool visible) { this->state.visible = visible; };

		inline const BlockType& getType() { return this->blockType; };
	private:
		BlockState state;
		BlockType blockType;
	};
}

namespace std
{
	template<> struct std::hash<GameComponents::BlockState>
	{
		std::size_t operator()(GameComponents::BlockState const& s) const noexcept
		{
			std::size_t h1 = std::hash<bool>{}(s.visible);
			return h1; // or use boost::hash_combine (see Discussion)
		}
	};
}