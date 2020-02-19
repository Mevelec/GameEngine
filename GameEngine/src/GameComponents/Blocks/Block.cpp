#include "hzpch.h"
#include "Block.h"

#include "GameEngine/Renderer/Renderer.h"

namespace GameComponents {
	BlockRegistery::BlockRegistery()
	{
		GE_PROFILE_FUNCTION();

		this->cubeTransform.reset(new GameEngine::Transform());

		//this->cube = GameEngine::CreateRef<GameEngine::Cube>();

		// SHADERS
		this->shaderLib.load("flat", "assets/shaders/FlatColor.glsl");
		this->shaderLib.load("default", "assets/shaders/Default.glsl");
		this->shaderLib.load("texture2D", "assets/shaders/Texture2D.glsl");
		this->shaderLib.load("textureCoordinates", "assets/shaders/TextureCoordinates.glsl");

		// MATERIALS
		GameEngine::Ref<GameEngine::Material> mat;

		mat = GameEngine::MaterialParser::getInstance().loadJson("assets/Materials/sample/configuration.json");
		this->materialLib.add("sample", mat);

		mat = GameEngine::CreateRef<GameEngine::Material>("flat", this->shaderLib.get("flat"));
		mat->addComponent("u_Color", glm::vec3(50, 50, 50) / glm::vec3(255));
		this->materialLib.add(mat);
	}

	void BlockRegistery::renderBlock(BlockType type, glm::vec3 position)
	{
		/*
		GE_PROFILE_FUNCTION();

		if (type == BlockType::Stone)
		{
		this->cubeTransform->setPostion(position);
			this->cubeTransform->setScale(1.0f);
			auto a = this->cube->getVertexArray();
			GameEngine::IRenderer::Submit(
				this->materialLib.get("flat"),
				this->cube->getVertexArray(),
				this->cubeTransform->getTransform()
			);
			return;
		}
		else if (type == BlockType::Dirt)
		{
			//GE_INFO("Render dirt at {0} {1} {2}", position.x, position.y, position.z);
			this->cubeTransform->setPostion(position);
			this->cubeTransform->setScale(1.0f);
			GameEngine::IRenderer::Submit(
				this->materialLib.get("flat"),
				this->cube->getVertexArray(),
				this->cubeTransform->getTransform()
			);
			return;
		}
		
		else if (type == BlockType::Grass)
		{
			this->cubeTransform->setPostion(position);
			this->cubeTransform->setScale(1.0f);
			GameEngine::IRenderer::Submit(
				this->materialLib.get("flat"),
				this->cube->getVertexArray(),
				this->cubeTransform->getTransform()
			);
			return;
		}
		*/
	}
}