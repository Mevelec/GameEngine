#include "hzpch.h"

#include <stdlib.h>

#include "OcTree/SVO/OcTreeDefault.h"
#include "Noise/Noise.h"
#include "GameEngine/Renderer/Renderer.h"

#include "Chunk.h"

namespace GameComponents {
	Chunk::Chunk(const glm::vec3& position)
	{
		GE_PROFILE_FUNCTION();

		this->position = position;

		this->chunk = GameEngine::CreateScope<OcTree::OcTreeDefault< GameEngine::Ref<Block> >>(4);


		int chunkW = chunk->getWidth();
		GameEngine::Noise noise(chunkW, chunkW);
		noise.loadNoiseAt(this->position.x, this->position.z, 0);

		for (int x = 0; x <= chunkW - 1; x++)
		{
			for (int z = 0; z <= chunkW - 1; z++)
			{
				float v = noise.get(x, z, 0) ;
				if (v < 0)
					v = 0;
				v = abs(v);
				float height = v * 20 + 8;
				for (int y = 0 + this->position.y * chunkW; y < height; y++)
				{
					auto state = GameComponents::BlockState();
					state.visible = true;
					auto bl = BlockManager::getInstance().getBlock(GameComponents::BlockType::Grass, state);

					chunk->set(bl, x, y, z);
				}
			}
		}

		auto state = GameComponents::BlockState();
		state.visible = false;
		auto bl = BlockManager::getInstance().getBlock(GameComponents::BlockType::Stone, state);
		chunk->set(bl, 0, 0, 0);

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

		GameEngine::Ref<GameEngine::Texture> dirt = GameEngine::Texture2D::Create(1, 1);
		uint32_t a = 0xffffffff;
		dirt->setData(&a, sizeof(uint32_t));
		GameEngine::Ref<GameEngine::Texture> grass = GameEngine::Texture2D::Create("assets/textures/Blocks/grass.png");
		GameEngine::Ref<GameEngine::Texture> stone = GameEngine::Texture2D::Create("assets/textures/Blocks/stone.png");

		GameEngine::Ref<GameEngine::Sampler> sampler = GameEngine::Sampler::Create();
		sampler->add(dirt, 0);
		sampler->add(grass, 1);
		sampler->add(stone, 1);


		mat->addComponent("u_Textures", sampler);


		this->materialLib.add(mat);
	}

	bool Chunk::generateVA()
	{
		GE_PROFILE_FUNCTION();

		// VertexBuffer
		GameEngine::Scope<GameEngine::DynamicGeometry> a = GameEngine::CreateScope<GameEngine::DynamicGeometry>();
		
		int chunkW = chunk->getWidth();
		for (int x = 0; x <= chunkW - 1; x++)
		{
			for (int y = 0; y <= chunkW - 1; y++)
			{
				for (int z = 0; z <= chunkW - 1; z++)
				{
					glm::vec3 pos(x + this->position.x * chunkW, y + this->position.y * chunkW, z + this->position.z * chunkW);
					auto block = this->chunk->get(x, y, z);
					if ( block != nullptr && block->getType() == GameComponents::BlockType::Grass)
					{
						auto ref = GameEngine::Cube::CreateCube(pos, {0.2, 0.9, 0.2, 1.0}, 1.0f);
						a->add(
							&ref[0], GameEngine::Cube::vCount, GameEngine::Cube::vStride / sizeof(float),
							GameEngine::Cube::indices, GameEngine::Cube::iCount
						);
					}
					else if(block != nullptr && block->getType() == GameComponents::BlockType::Stone)
					{
						auto ref = GameEngine::Cube::CreateCube(pos, { 0.6, 0.6, 0.6, 1.0 }, 0.0f);
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

	GameEngine::Ref<Block> Chunk::get(int posx, int posy, int posz) {
		GE_PROFILE_FUNCTION();

		return this->chunk->get(posx, posy, posz);
	};
	void Chunk::set(GameEngine::Ref<Block> value, int posx, int posy, int posz) {
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