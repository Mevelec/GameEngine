#include "hzpch.h"

#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine {
	Geometry::Geometry(BufferLayout layout)
	{
		this->vertices = std::vector<float>();
		this->indices = std::vector<uint32_t>();

		this->layout = layout;
	}

	void Geometry::createVA()
	{
		if (this->vertices.empty() || this->indices.empty())
		{
			this->VA = nullptr;
			return;
		}

		GameEngine::Ref<GameEngine::IVertexBuffer> VB = GameEngine::IVertexBuffer::Create(&this->vertices[0], this->vertices.size() * sizeof(float));

		VB->setLayout(this->layout);

		this->VA = GameEngine::VertexArray::Create();
		this->VA->addVertexBuffer(VB);

		GameEngine::Ref<GameEngine::IIndexBuffer> IB = GameEngine::IIndexBuffer::Create(&this->indices[0], this->indices.size());
		this->VA->setIndexBuffer(IB);
	}

	bool Geometry::add(Geometry& geo)
	{
		// check vertex layouts if false return false and no merge
		for (auto it = geo.getVertices().begin(); it != geo.getVertices().end(); it++)
		{
			this->vertices.push_back(*it);
		}
		for (auto it = geo.getIndices().begin(); it != geo.getIndices().end(); it++)
		{
			this->indices.push_back(*it + this->verticesOffset);
		}

		auto a = geo.getVertices().size();
		auto i = geo.getLayout().getStride() / sizeof(float);
		auto b = a / i;
		this->verticesOffset += b;

		return true;
	}
}

// STATIC GEOMETRY
namespace GameEngine {

	StaticGeometry::StaticGeometry(BufferLayout layout, std::vector<float> vertices, std::vector<uint32_t> indices)
		: Geometry(layout)
	{
		this->vertices = vertices;
		this->indices = indices;
	}
}