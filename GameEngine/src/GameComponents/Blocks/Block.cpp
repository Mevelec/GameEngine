#include "hzpch.h"
#include "Block.h"

#include "GameEngine/Renderer/Renderer.h"

namespace GameComponents {
	BlockRegistery::BlockRegistery()
	{
		//////// SQUARE ////////
		this->cubeTransform.reset(new GameEngine::Transform());
		//Vertex Array
		this->cubeVA = GameEngine::VertexArray::Create();
		float squareVertices[5 * 8] = {
			-1, -1.0f, -1.0f, 0.0f, 0.0f,
			 1, -1.0f, -1.0f, 1.0f, 0.0f,
			 1,  1.0f, -1.0f, 1.0f, 1.0f,
			-1,  1.0f, -1.0f, 0.0f, 1.0f,

			
			-1, -1.0f,  1.0f, 0.0f, 0.0f,
			 1, -1.0f,  1.0f, 1.0f, 0.0f,
			 1,  1.0f,  1.0f, 1.0f, 1.0f,
			-1,  1.0f,  1.0f, 0.0f, 1.0f,

		};
		GameEngine::Ref<GameEngine::IVertexBuffer> squareVB;
		squareVB.reset(GameEngine::IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		GameEngine::BufferLayout squareLayout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float2, "a_TextCoord" }
		};
		squareVB->setLayout(squareLayout);
		this->cubeVA->addVertexBuffer(squareVB);

		//Index Buffer
		unsigned int squareIndices[12 * 3] = { 
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			0, 1, 3,
			3, 4, 0,

			3, 2, 6,
			6, 7, 3,

			4, 0, 3,
			3, 7, 4,

			5, 1, 2,
			2, 6, 5,
		};
		GameEngine::Ref<GameEngine::IIndexBuffer> squareIB;
		squareIB.reset(GameEngine::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		this->cubeVA->setIndexBuffer(squareIB);

		// SHADERS
		this->shaderLib.load("flat", "assets/shaders/FlatColor.glsl");
		this->shaderLib.load("default", "assets/shaders/Default.glsl");
		this->shaderLib.load("texture2D", "assets/shaders/Texture2D.glsl");
		this->shaderLib.load("textureCoordinates", "assets/shaders/TextureCoordinates.glsl");

		// MATERIALS
		GameEngine::Ref<GameEngine::Material> mat;

		mat = GameEngine::MaterialParser::getInstance().loadJson("assets/Materials/sample/configuration.json");
		this->materialLib.add("sample", mat);

		mat =  GameEngine::CreateRef<GameEngine::Material>("dirt", this->shaderLib.get("default"));
		mat->addComponent("u_Color", glm::vec4(107, 91, 46, 255) / glm::vec4(255));
		this->whiteTexture = GameEngine::Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		this->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));
		mat->addComponent("u_Texture", this->whiteTexture, 0);
		this->materialLib.add(mat);

		mat = GameEngine::CreateRef<GameEngine::Material>("stone", this->shaderLib.get("flat"));
		mat->addComponent("u_Color", glm::vec3(50, 50, 50) / glm::vec3(255));
		this->materialLib.add(mat);

		mat = GameEngine::CreateRef<GameEngine::Material>("grass", this->shaderLib.get("flat"));
		mat->addComponent("u_Color", glm::vec3(49, 151, 63) / glm::vec3(255));
		this->materialLib.add(mat);

		mat = GameEngine::CreateRef<GameEngine::Material>("textureCoordinates", this->shaderLib.get("textureCoordinates"));
		this->materialLib.add(mat);

		mat = GameEngine::CreateRef<GameEngine::Material>("texture2D", this->shaderLib.get("texture2D"));
		mat->addComponent("u_Color", glm::vec4(1, 0, 0, 1));
		this->uv_texture = GameEngine::Texture2D::Create("assets/textures/uv_check.png");
		this->texture2 = GameEngine::Texture2D::Create("assets/textures/disney.png");
		mat->addComponent("u_Texture", this->uv_texture, 1);
		this->materialLib.add(mat);
	}

	void BlockRegistery::renderBlock(BlockType type, glm::vec3 position)
	{
		if (type == BlockType::Stone)
		{
		this->cubeTransform->setPostion(position);
			this->cubeTransform->setScale(1.0f);

			GameEngine::IRenderer::Submit(
				this->materialLib.get("stone"),
				this->cubeVA,
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
				this->materialLib.get("dirt"),
				this->cubeVA,
				this->cubeTransform->getTransform()
			);
			return;
		}
		
		else if (type == BlockType::Grass)
		{
			this->cubeTransform->setPostion(position);
			this->cubeTransform->setScale(1.0f);
			GameEngine::IRenderer::Submit(
				this->materialLib.get("grass"),
				this->cubeVA,
				this->cubeTransform->getTransform()
			);
			return;
		}
	}
}