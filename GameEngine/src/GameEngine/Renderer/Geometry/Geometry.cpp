#include "hzpch.h"

#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine {

	DynamicGeometry::DynamicGeometry(const GameEngine::BufferLayout& layout)
	{

		this->layout = layout;

		this->vertices = std::vector<float>();
		this->indices = std::vector<uint32_t>();

		this->update();
	}

	void DynamicGeometry::update()
	{
		this->verticesSize = this->layout.getStride() * this->vertices.size() / 6;
		this->indicesSize = sizeof(uint32_t) * this->indices.size();
	}

	float* DynamicGeometry::getVertices(glm::vec3 position) {
		return &this->vertices[0];
	}

	uint32_t* DynamicGeometry::getIndices() {
		return &this->indices[0];
	}

	void DynamicGeometry::add(float* vertices, uint32_t sizeV, uint32_t* indices, uint32_t sizeI)
	{
		int offsetI = this->verticesSize / this->layout.getStride();
		for (uint32_t it = 0; it < sizeI; it += 1)
		{
			this->indices.push_back(indices[it] + offsetI);
		}

		int countV = sizeV / sizeof(float);
		for (uint32_t it = 0; it < countV; it += 1)
		{
			this->vertices.push_back(vertices[it]);
		}

		this->update();
	}

	void DynamicGeometry::createVA()
	{
		GameEngine::Ref<GameEngine::IVertexBuffer> VB = GameEngine::IVertexBuffer::Create(this->getVertices(), this->getVerticesSize());

		VB->setLayout(layout);

		this->VA = GameEngine::VertexArray::Create();
		this->VA->addVertexBuffer(VB);

		GameEngine::Ref<GameEngine::IIndexBuffer> IB = GameEngine::IIndexBuffer::Create(this->getIndices(), this->getIndicesSize() / sizeof(uint32_t));
		this->VA->setIndexBuffer(IB);
	}

	GameEngine::Ref<GameEngine::VertexArray> DynamicGeometry::getVA() { return this->VA; }

}