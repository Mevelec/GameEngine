#pragma once

#include <glm/glm.hpp>
#include <array>
#include <vector>

#include "GameEngine/Renderer/Buffer/Buffer.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"

namespace GameEngine {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoords;
		float texId;
	};

	class Geometry
	{
	public:
		virtual float* getVertices() = 0;
		virtual uint32_t* getIndices() = 0;

	protected:
		uint32_t indicesSize;
	};



	class DynamicGeometry : Geometry
	{
	public:
		DynamicGeometry();

		virtual float* getVertices() override;
		virtual uint32_t* getIndices() override;

		void add(float* vertices, const uint32_t countV, const uint32_t vStride, const uint32_t* indices, const uint32_t countI);

		void createVA();

		GameEngine::Ref<GameEngine::VertexArray> getVA();

	protected:
		GameEngine::Ref<GameEngine::VertexArray> VA;

		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		uint32_t verticesOffset = 0;
	};
}