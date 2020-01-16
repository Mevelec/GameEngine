#include "Block.h"

namespace Blocks {
	BlockRegistery::BlockRegistery()
	{
		//////// SQUARE ////////
		this->cubeTransform.reset(new GameEngine::Transform());
		//Vertex Array
		this->cubeVA.reset(GameEngine::VertexArray::Create());
		float squareVertices[5 * 8] = {
			-1, -1.0f, -1.0f, 1.0f, 0.0f,
			 1, -1.0f, -1.0f, 0.0f, 1.0f,
			 1,  1.0f, -1.0f, 0.0f, 0.0f,
			-1,  1.0f, -1.0f, 0.0f, 0.0f,

			
			-1, -1.0f,  1.0f, 1.0f, 0.0f,
			 1, -1.0f,  1.0f, 0.0f, 1.0f,
			 1,  1.0f,  1.0f, 0.0f, 0.0f,
			-1,  1.0f,  1.0f, 0.0f, 0.0f,

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
		// Flat
		this->shaderLib.load("flat", "assets/shaders/FlatColor.glsl");
		// Texture 
		this->textureShader = GameEngine::Shader::Create("assets/shaders/Texture2D.glsl");

		// TEXTURE
		this->uv_texture = GameEngine::Texture2D::Create("assets/textures/UV_check.png");

		// MATERIAL
		auto mat = GameEngine::Material::Create("default");
		this->materialLib.add(mat);

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(this->textureShader)->bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(this->textureShader)->uploadUniformInt("u_Texture", 0);
	}

	void BlockRegistery::renderBlock(BlockType type, glm::vec3 position)
	{
		auto flatShader = this->shaderLib.get("flat");
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(flatShader)->bind();

		if(type == BlockType::Dirt)
			std::dynamic_pointer_cast<GameEngine::OpenGLShader>(flatShader)->uploadUniformFloat3("u_Color", glm::vec3(1, 0, 0));
		else if(type == BlockType::Sand)
			std::dynamic_pointer_cast<GameEngine::OpenGLShader>(flatShader)->uploadUniformFloat3("u_Color", glm::vec3(0, 1, 0));
		else if (type == BlockType::Grass)
			std::dynamic_pointer_cast<GameEngine::OpenGLShader>(flatShader)->uploadUniformFloat3("u_Color", glm::vec3(0, 0, 1));

		this->cubeTransform->setPostion(position);
		this->cubeTransform->setScale(1.0f);
		GameEngine::IRenderer::Submit(
			flatShader,
			this->cubeVA,
			this->cubeTransform->getTransform()
		);
	}
}