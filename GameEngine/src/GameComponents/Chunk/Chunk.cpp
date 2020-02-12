#include "hzpch.h"

#include "OcTree/SVO/OcTreeDefault.h"
#include "GameEngine/Renderer/Renderer.h"

#include "Chunk.h"

namespace GameComponents {
	Chunk::Chunk()
	{
		GE_PROFILE_FUNCTION();

		this->chunk = GameEngine::CreateScope<OcTree::OcTreeDefault<BlockType>>(2);

		for (int x = 0; x <= chunk->getWidth() - 1; x++)
		{
			for (int z = 0; z <= chunk->getWidth() - 1; z++)
			{
				for (int y = 0; y <= chunk->getWidth() - 1; y++)
				{
					if (y > chunk->getWidth() - 2)
						chunk->set(GameComponents::BlockType::Grass, x, y, z);
					else
						chunk->set(GameComponents::BlockType::Dirt, x, y, z);
				}
			}
		}
		chunk->set(GameComponents::BlockType::Stone, 0, 0, 0);

		this->generateVA();

		// SHADERS
		this->shaderLib.load("flat", "assets/shaders/FlatColor.glsl");

		// MATERIALS
		GameEngine::Ref<GameEngine::Material> mat;

		mat = GameEngine::MaterialParser::getInstance().loadJson("assets/Materials/sample/configuration.json");
		this->materialLib.add("sample", mat);

		mat = GameEngine::CreateRef<GameEngine::Material>("flat", this->shaderLib.get("flat"));
		mat->addComponent("u_Color", glm::vec3(50, 50, 50) / glm::vec3(255));
		this->materialLib.add(mat);
	}

	bool Chunk::generateVA()
	{
		GE_PROFILE_FUNCTION();

		// VertexBuffer
		cube = GameEngine::CreateScope<GameEngine::Cube>();
		GameEngine::Scope<GameEngine::DynamicGeometry> a = GameEngine::CreateScope<GameEngine::DynamicGeometry>();
		
		a->addVertices(cube->getVertices(), cube->getVerticesSize() / sizeof(float));
		a->addIndices(cube->getIndices(), cube->getIndicesSize() / sizeof(uint32_t));

		a->createVA();
		this->VA = a->getVA();


		for (int x = 0; x <= chunk->getWidth() - 1; x++)
		{
			for (int z = 0; z <= chunk->getWidth() - 1; z++)
			{
				for (int y = 0; y <= chunk->getWidth() - 1; y++)
				{

				}
			}
		}
		return true;
	}

	BlockType& Chunk::get(int posx, int posy, int posz) {
		GE_PROFILE_FUNCTION();

		return this->chunk->get(posx, posy, posz);
	};
	void Chunk::set(BlockType value, int posx, int posy, int posz) {
		GE_PROFILE_FUNCTION();

		this->chunk->set(value, posx, posy, posz);
	};

	void Chunk::render()
	{
		GE_PROFILE_FUNCTION();
		GameEngine::IRenderer::Submit(
			this->materialLib.get("flat"),
			this->VA
		);
		
		/*GE_PROFILE_FUNCTION();

		for (int x = 0; x <= chunk->getWidth() - 1; x++)
		{
			for (int z = 0; z <= chunk->getWidth() - 1; z++)
			{
				for (int y = 0; y <= chunk->getWidth() - 1; y++)
				{
					GE_PROFILE_SCOPE("Render Block of Chunk");

					GameComponents::BlockRegistery::getInstance().renderBlock(chunk->get(x, y, z), glm::vec3(x * 2, y * 2, z * 2));
				}
			}
		}*/
		
	}
}