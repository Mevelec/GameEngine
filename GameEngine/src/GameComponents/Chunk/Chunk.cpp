#include "hzpch.h"

#include <stdlib.h>

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
					int seed = (y << 16 |x << z);

					std::srand(seed);
					bool rand = (std::rand() % 100) < 50;

					if (rand)
						chunk->set(GameComponents::BlockType::Grass, x, y, z);

				}
			}
		}
		chunk->set(GameComponents::BlockType::Stone, 0, 0, 0);

		this->generateVA();

		// SHADERS
		this->shaderLib.load("default", "assets/shaders/Default.glsl");

		// MATERIALS
		GameEngine::Ref<GameEngine::Material> mat;

		mat = GameEngine::MaterialParser::getInstance().loadJson("assets/Materials/sample/configuration.json");
		this->materialLib.add("sample", mat);

		mat = GameEngine::CreateRef<GameEngine::Material>("default", this->shaderLib.get("default"));
		mat->addComponent("u_Color", glm::vec4(255, 255, 255, 255) / glm::vec4(255));
		mat->addComponent("u_TilingFactor", 1.0f);

		GameEngine::Ref<GameEngine::Texture> uv_texture = GameEngine::Texture2D::Create("assets/textures/uv_check.png");
		GameEngine::Ref<GameEngine::Texture> tex = GameEngine::Texture2D::Create("assets/textures/disney.png");

		GameEngine::Ref<GameEngine::Sampler> sampler = GameEngine::Sampler::Create();
		sampler->add(uv_texture, 0);
		sampler->add(tex, 1);

		mat->addComponent("u_Textures", sampler);


		this->materialLib.add(mat);
	}

	bool Chunk::generateVA()
	{
		GE_PROFILE_FUNCTION();

		// VertexBuffer
		GameEngine::Scope<GameEngine::DynamicGeometry> a = GameEngine::CreateScope<GameEngine::DynamicGeometry>();
		
		for (int x = 0; x <= chunk->getWidth() - 1; x++)
		{
			for (int z = 0; z <= chunk->getWidth() - 1; z++)
			{
				for (int y = 0; y <= chunk->getWidth() - 1; y++)
				{
					if (this->chunk->get( x, y, z ) == GameComponents::BlockType::Grass)
					{
						auto ref = GameEngine::Cube::CreateCube(glm::fvec3(x, y, z), 1.0f);
						a->add(
							&ref[0], GameEngine::Cube::vCount, GameEngine::Cube::vStride / sizeof(float),
							GameEngine::Cube::indices, GameEngine::Cube::iCount
						);
					}
					else
					{
						auto ref = GameEngine::Cube::CreateCube(glm::fvec3(x, y, z), 0.0f);
						a->add(
							&ref[0], GameEngine::Cube::vCount, GameEngine::Cube::vStride / sizeof(float),
							GameEngine::Cube::indices, GameEngine::Cube::iCount
						);
					}
				}
			}
		}

		a->createVA();
		this->VA = a->getVA();
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
			this->materialLib.get("default"),
			this->VA
		);
	}
}