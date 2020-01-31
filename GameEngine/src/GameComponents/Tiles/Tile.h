#pragma once
#include "GameEngine/Renderer/Material/Shader.h"
#include "GameEngine/Renderer/Material/MaterialLibrary.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"
#include "GameEngine/Core/Transform/Transform.h"

#include <glm/gtc/type_ptr.hpp>

namespace GameComponents {
	enum class TilesType {
		TileType_Default = 0,

		Grass,
		Dirt,
		Water,
		Stone,
		Wood,
		Sand,

		TileType_NumTypes,
	};
	class Tile
	{
	public:
		Tile();
		~Tile();

		inline const bool isActive() const { return this->active; };
		inline void setActive(bool active) { this->active = active; };
	private:
		bool active;
		TilesType tileType;
	};
	
	class TilesRegistery
	{
	public:
		void renderTile(TilesType type, glm::vec3 position);

	private:
		GameEngine::ShaderLibrary shaderLib;
		GameEngine::MaterialLibrary materialLib;

		GameEngine::Ref<GameEngine::Texture> uv_texture;

		GameEngine::Ref<GameEngine::VertexArray> squareVA;
		GameEngine::Ref<GameEngine::Transform>   squareTransform;
	public:
		static TilesRegistery& getInstance()
		{
			static TilesRegistery    instance;
			return instance;
		}
	private:
		TilesRegistery();

		// C++ 11
		// =======
		// We can use the better technique of deleting the methods
		// we don't want.
	public:
		TilesRegistery(TilesRegistery const&) = delete;
		void operator=(TilesRegistery const&) = delete;
	};
}

