#include "hzpch.h"
#include "Tile.h"

#include "GameEngine/Renderer/Renderer.h"

namespace GameComponents {
	TilesRegistery::TilesRegistery()
	{
		//////// SQUARE ////////
		this->squareTransform.reset(new GameEngine::Transform());
		//Vertex Array
		this->squareVA = GameEngine::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-1, -1.0f, 0.0f, 1.0f, 1.0f,
			 1, -1.0f, 0.0f, 0.0f, 1.0f,
			 1,  1.0f, 0.0f, 0.0f, 0.0f,
			-1,  1.0f, 0.0f, 1.0f, 0.0f,
		};
		GameEngine::Ref<GameEngine::IVertexBuffer> squareVB = GameEngine::IVertexBuffer::Create(squareVertices, sizeof(squareVertices));
		GameEngine::BufferLayout squareLayout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float2, "a_TextCoord" }
		};
		squareVB->setLayout(squareLayout);
		this->squareVA->addVertexBuffer(squareVB);

		//Index Buffer
		unsigned int squareIndices[2 * 3] = { 
			0, 1, 2,
			2, 3, 0,
		};
		GameEngine::Ref<GameEngine::IIndexBuffer> squareIB = GameEngine::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		this->squareVA->setIndexBuffer(squareIB);

		// SHADERS
		// Flat
		GameEngine::Ref<GameEngine::Shader> shader;
		GameEngine::Ref<GameEngine::Material> mat;

		shader = this->shaderLib.load("flat",               "assets/shaders/FlatColor.glsl");
		mat = GameEngine::CreateRef<GameEngine::Material>(shader);
		this->materialLib.add(mat);

		shader = this->shaderLib.load("textureCoordinates", "assets/shaders/TextureCoordinates.glsl");
		mat = GameEngine::CreateRef<GameEngine::Material>("textureCoordinates", shader);
		this->materialLib.add(mat);

		shader = this->shaderLib.load("texture2D",          "assets/shaders/Texture2D.glsl");
		mat = GameEngine::CreateRef<GameEngine::Material>("texture2D", shader);
		this->materialLib.add(mat);



		// TEXTURE
		shader->bind();
		this->uv_texture = GameEngine::Texture2D::Create("assets/textures/uv_check.png");
		shader->setInt("u_Texture", 0);
	}

	void TilesRegistery::renderTile(TilesType type, glm::vec3 position)
	{
		GameEngine::Ref<GameEngine::Shader> shader;
		//GameEngine::Ref<GameEngine::Material> mat;

		if (type == TilesType::Dirt)
		{
			shader = this->shaderLib.get("flat");
			shader->bind();
			shader->setFloat3("u_Color", glm::vec3(1, 0, 0));
		}
		else if (type == TilesType::Sand)
		{
			shader = this->shaderLib.get("flat");
			shader->bind();
			shader->setFloat3("u_Color", glm::vec3(0, 1, 0));
		}
		else if (type == TilesType::Grass)
		{
			shader = this->shaderLib.get("texture2D");
			shader->bind();
			shader->setFloat4("u_Color", glm::vec4(1));
			this->uv_texture->bind();

		}

		this->squareTransform->setPostion(position);
		this->squareTransform->setScale(1.0f);
		GameEngine::IRenderer::Submit(
			shader,
			this->squareVA,
			this->squareTransform->getTransform()
		);
	}
}