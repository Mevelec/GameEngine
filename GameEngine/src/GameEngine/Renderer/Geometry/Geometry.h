#pragma once

#include <glm/glm.hpp>
#include <array>
#include <vector>

#include "GameEngine/Renderer/Buffer/Buffer.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"

namespace GameEngine {

	class Geometry
	{
	public:
		Geometry(BufferLayout layout);

		void createVA();
		const GameEngine::Ref<GameEngine::VertexArray>& getVA() { this->createVA(); return this->VA; };

		const BufferLayout& getLayout() { return this->layout; };

		bool add(Geometry& geo);

		const std::vector<float>& getVertices() { return this->vertices; };
		const std::vector<uint32_t>& getIndices() { return this->indices; };
	protected:
		BufferLayout layout;

		GameEngine::Ref<GameEngine::VertexArray> VA;

		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		uint32_t verticesOffset = 0;
	};

	class StaticGeometry : public Geometry
	{
	public:
		StaticGeometry::StaticGeometry(BufferLayout layout, std::vector<float> vertices, std::vector<uint32_t> indices);
	};
}