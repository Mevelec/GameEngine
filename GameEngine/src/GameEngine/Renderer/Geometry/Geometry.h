#pragma once

#include <glm/glm.hpp>

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

	class DynamicGeometry
	{
	public:
		virtual const Ref<VertexArray>& getVertexArray() { return this->VA; };

	protected:
		Ref<VertexArray> VA;

		float* vertices;
	};

	class Square : public Geometry
	{
	private:
		float vertices[4 * 3] = {
				-0.5, -0.5f, 0.0f,
				 0.5, -0.5f, 0.0f,
				 0.5,  0.5f, 0.0f,
				-0.5,  0.5f, 0.0f,
		};;
		uint32_t indices[2 * 3] = {
				0, 1, 2,
				2, 3, 0,
		};
	public:
		Square()
		{
			this->verticesSize = sizeof(this->vertices);
			this->indicesSize =sizeof(this->indices);
		}

		virtual float* getVertices(glm::vec3 position = glm::vec3(0.0f)) override {
			return this->vertices;
		}
		virtual uint32_t* getIndices() override {
			return this->indices;
		}

	};

	class Cube : public Geometry
	{
	private:
		float vertices[3 * 8] = {
				-0.5, -0.5f, -0.5f,
				 0.5, -0.5f, -0.5f,
				 0.5,  0.5f, -0.5f,
				-0.5,  0.5f, -0.5f,
				-0.5, -0.5f,  0.5f,
				 0.5, -0.5f,  0.5f,
				 0.5,  0.5f,  0.5f,
				-0.5,  0.5f,  0.5f,
		};
		uint32_t indices[12 * 3] = {
				0, 1, 2,
				2, 3, 0,

				4, 5, 6,
				6, 7, 4,

				0, 1, 3,
				3, 4, 0,

				3, 2, 6,
				6, 7, 3,

				4, 0, 3,
				3, 7, 4,

				5, 1, 2,
				2, 6, 5,
		};
	public:
		Cube()
		{
			this->verticesSize = sizeof(this->vertices);
			this->indicesSize = sizeof(this->indices);
		}
		virtual float* getVertices(glm::vec3 position = glm::vec3(0.0f)) override {
			return this->vertices;
		}
		virtual uint32_t* getIndices() override {
			return this->indices;
		}
	};
}