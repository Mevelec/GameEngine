#pragma once

#include <GameEngine.h>
#include "Plateform/OpenGl/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>
namespace Blocks {
	enum BlockType {
		BlockType_Default = 0,

		Grass,
		Dirt,
		Water,
		Stone,
		Wood,
		Sand,

		BlockType_NumTypes,
	};
	class Block
	{
	public:
		Block();
		~Block();

		inline const bool isActive() const { return this->active; };
		inline void setActive(bool active) { this->active = active; };
	private:
		bool active;
		BlockType blockType;
	};
	
	class BlockRegistery
	{
	public:
		void renderBlock(BlockType type, glm::vec3 position);

	private:
		GameEngine::ShaderLibrary shaderLib;
		GameEngine::MaterialLibrary materialLib;
		GameEngine::Ref<GameEngine::Shader> textureShader;
		GameEngine::Ref<GameEngine::Texture> uv_texture;

		GameEngine::Ref<GameEngine::VertexArray> cubeVA;
		GameEngine::Ref<GameEngine::Transform>   cubeTransform;
	public:
		static BlockRegistery& getInstance()
		{
			static BlockRegistery    instance;
			return instance;
		}
	private:
		BlockRegistery();

		// C++ 11
		// =======
		// We can use the better technique of deleting the methods
		// we don't want.
	public:
		BlockRegistery(BlockRegistery const&) = delete;
		void operator=(BlockRegistery const&) = delete;
	};
}
