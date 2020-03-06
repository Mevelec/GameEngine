#include "hzpch.h"

#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine {

	DynamicGeometry::DynamicGeometry()
	{
		this->vertices = std::vector<float>();
		this->indices = std::vector<uint32_t>();

		this->indicesSize = sizeof(uint32_t) * this->indices.size();
	}

	float* DynamicGeometry::getVertices() {
		return &this->vertices[0];
	}

	uint32_t* DynamicGeometry::getIndices() {
		return &this->indices[0];
	}

	void DynamicGeometry::add(float* vertices, const uint32_t countV, const uint32_t vStride, const uint32_t* indices, const uint32_t countI)
	{
		for (uint32_t it = 0; it < countI; it += 1)
		{
			this->indices.push_back(indices[it] + this->verticesOffset);
		}

		for (uint32_t it = 0; it < countV * vStride; it += 1)
		{
			this->vertices.push_back(vertices[it]);
		}

		this->verticesOffset += countV;
		this->indicesSize = sizeof(uint32_t) * this->indices.size();
	}

	void DynamicGeometry::createVA()
	{
		if (this->vertices.empty() || this->indices.empty())
		{
			this->VA = nullptr;
			return;
		}
		auto a = this->getVertices();
		auto b = this->vertices.size();
		auto c = sizeof(float);
		GameEngine::Ref<GameEngine::IVertexBuffer> VB = GameEngine::IVertexBuffer::Create(this->getVertices(), this->vertices.size() * sizeof(float));

		GameEngine::BufferLayout layout = {
				{ GameEngine::ShaderDataType::Float3, "a_Position"},
				{ GameEngine::ShaderDataType::Float4, "a_Color"},
				{ GameEngine::ShaderDataType::Float2, "a_TexCoord"},
				{ GameEngine::ShaderDataType::Float, "a_TexId"},
		};

		VB->setLayout(layout);

		this->VA = GameEngine::VertexArray::Create();
		this->VA->addVertexBuffer(VB);

		GameEngine::Ref<GameEngine::IIndexBuffer> IB = GameEngine::IIndexBuffer::Create(this->getIndices(), this->indices.size());
		this->VA->setIndexBuffer(IB);
	}

	GameEngine::Ref<GameEngine::VertexArray> DynamicGeometry::getVA() { return this->VA; }

}