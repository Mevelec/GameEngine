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

		this->generate();
		this->load();
		this->build();
	}

	void Chunk::generate()
	{
		GE_PROFILE_FUNCTION();

		this->chunk = GameEngine::CreateScope<OcTree::OcTreeDefault< GameEngine::Ref<Block> >>(4);


		int chunkW = chunk->getWidth();
		GameEngine::Noise noise(chunkW, chunkW);
		noise.loadNoiseAt(this->position.x, this->position.z, 0);


		
		for (int x = 0; x <= chunkW - 1; x++)
		{
			for (int z = 0; z <= chunkW - 1; z++)
			{
				float v = noise.get(x, z, 0);
				if (v < 0)
					v = 0;
				v = abs(v);
				float height = v * 20 + 8;
				for (int y = 0 + this->position.y * chunkW; y < height; y++)
				{
					auto state = GameComponents::BlockState();
					state.visible = false;
					auto bl = BlockManager::getInstance().getBlock(GameComponents::BlockType::Grass, state);
					chunk->set(bl, x, y, z);
				}
			}
		}
		
	}

	void Chunk::load()
	{
		GE_PROFILE_FUNCTION();

		//find a not empty block start from 0,0,0 
		//check if this block have an empty neighboor
		//if yes set visible if not set unvisible

		//iterate over chunck
		//ifblock != empty
		// if have an empty neighboor display

		int chunkW = chunk->getWidth() -1;
		for (int x = 0; x <= chunkW; x++)
		{
			for (int y = 0; y <= chunkW; y++)
			{
				for (int z = 0; z <= chunkW; z++)
				{
					auto block = this->chunk->get(x, y, z);

					if (block != nullptr)
					{
						auto state = GameComponents::BlockState();
						state.visible = true;
						GameEngine::Ref<Block> ref = BlockManager::getInstance().getBlock(block->getType(), state);
						
						bool isSet = false;
						// X
						auto tmp = this->get(x -1, y, z, false);
						if ( tmp == nullptr && !isSet)
						{
							this->chunk->set(ref,
								x, y, z);
							isSet = true;
						}
						tmp = this->get(x +1, y, z, false);
						if (tmp == nullptr && !isSet)
						{
							this->chunk->set(ref,
								x, y, z);
							isSet = true;
						}
						// Y
						tmp = this->get(x, y -1, z, false);
						if (tmp == nullptr && !isSet)
						{
							this->chunk->set(ref,
								x, y, z);
							isSet = true;
						}
						tmp = this->get(x, y +1, z, false);
						if (tmp == nullptr && !isSet)
						{
							this->chunk->set(ref,
								x, y, z);
							isSet = true;
						}
						// Z
						tmp = this->get(x, y, z -1, false);
						if (tmp == nullptr && !isSet)
						{
							this->chunk->set(ref,
								x, y, z);
							isSet = true;
						}
						tmp = this->get(x, y, z +1, false);
						if (tmp == nullptr && !isSet)
						{
							this->chunk->set(ref,
								x, y, z);
							isSet = true;
						}
					}
				}
			}
		}

	}

	void Chunk::unload()
	{
		this->VA = nullptr;
	}

	void Chunk::build()
	{
		GE_PROFILE_FUNCTION();

		// VertexBuffer
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float4, "a_Color"},
			{ GameEngine::ShaderDataType::Float2, "a_TexCoord"},
			{ GameEngine::ShaderDataType::Float, "a_TexId"},
		};
		GameEngine::Scope<GameEngine::Geometry> a = GameEngine::CreateScope<GameEngine::Geometry>(layout);

		int chunkW = chunk->getWidth();
		for (int x = 0; x <= chunkW - 1; x++)
		{
			for (int y = 0; y <= chunkW - 1; y++)
			{
				for (int z = 0; z <= chunkW - 1; z++)
				{
					glm::vec3 pos(x + this->position.x * chunkW, y + this->position.y * chunkW, z + this->position.z * chunkW);
					auto block = this->get(x, y, z, false);
					if(block != nullptr && block->isVisible())
					{
						GameEngine::Faces faces{ 0, 0, 0, 0, 0, 0};
						{
							auto tmp = this->get(x - 1, y, z, false);
							if(tmp == nullptr)
								faces.left = true;
							tmp = this->get(x + 1, y, z, false);
							if (tmp == nullptr)
								faces.right = true;
							tmp = this->get(x, y - 1, z, false);
							if (tmp == nullptr)
								faces.bottom = true;
							tmp = this->get(x, y + 1, z, false);
							if (tmp == nullptr)
								faces.top = true;
							tmp = this->get(x, y, z - 1, false);
							if (tmp == nullptr)
								faces.front = true;
							tmp = this->get(x, y, z + 1, false);
							if (tmp == nullptr)
								faces.back = true;
						}

						if (  block->getType() == GameComponents::BlockType::Grass)
						{
							auto ref = GameEngine::CreateCube(faces, pos, { 0.2, 0.9, 0.2, 1.0 }, 1.0f);
							a->add(
								ref
							);
						}
						else if(block->getType() == GameComponents::BlockType::Stone)
						{
							auto ref = GameEngine::CreateCube(faces, pos, { 0.6, 0.6, 0.6, 1.0 }, 0.0f);
							a->add(
								ref
							);
						}
					}
				}
			}
		}

		a->createVA();
		this->VA = a->getVA();
	}

	GameEngine::Ref<Block> Chunk::get(int posx, int posy, int posz, bool checkNeighboors)  {
		if (!checkNeighboors)
		{
			int chunkW = this->chunk->getWidth() - 1;
			if ( (posx < 0 || posx > chunkW) || (posy < 0 || posy > chunkW) || (posz < 0 || posz > chunkW) ) //if is at border
			{
				return nullptr;
			}
		}
		return this->chunk->get(posx, posy, posz);
	};
	void Chunk::set(GameEngine::Ref<Block> value, int posx, int posy, int posz) {
		GE_PROFILE_FUNCTION();

		this->chunk->set(value, posx, posy, posz);
	};

	void Chunk::render()
	{
		GE_PROFILE_FUNCTION();

		if (this->VA != nullptr && this->active)
		{
			GameEngine::IRenderer::Submit(
				GameEngine::MaterialLibrary::getInstance().get("default"),
				this->VA
			);
		}
	}
}
