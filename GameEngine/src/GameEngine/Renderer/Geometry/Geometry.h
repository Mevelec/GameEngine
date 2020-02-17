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
		virtual float* getVertices(glm::vec3 position = glm::vec3(0.0f)) = 0;
		virtual const uint32_t getVerticesSize() { return this->verticesSize; };

		virtual uint32_t* getIndices() = 0;
		virtual const uint32_t getIndicesSize() { return this->indicesSize; };

	protected:
		uint32_t verticesSize;
		uint32_t indicesSize;
	};

	class DynamicGeometry : Geometry
	{
	public:
		DynamicGeometry(const GameEngine::BufferLayout& layout);

		void update();

		virtual float* getVertices(glm::vec3 position = glm::vec3(0.0f)) override;
		virtual uint32_t* getIndices() override;

		void add(float* vertices, uint32_t sizeV, uint32_t* indices, uint32_t sizeI);

		void createVA();

		GameEngine::Ref<GameEngine::VertexArray> getVA();

	protected:
		GameEngine::Ref<GameEngine::VertexArray> VA;

		std::vector<float> vertices;
		std::vector<uint32_t> indices;
		GameEngine::BufferLayout layout;
	};
}