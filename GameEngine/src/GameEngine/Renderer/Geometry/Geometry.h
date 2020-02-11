#pragma once

#include <glm/glm.hpp>

#include "GameEngine/Renderer/Buffer/Buffer.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"

namespace GameEngine {

	class Geometry
	{
	public:
		virtual float* getVertices() { return this->vertices; };
		virtual float* getVertices(glm::vec3 position) { return this->vertices; };

		virtual const uint32_t getVerticesSize() { return sizeof(this->verticesSize); };

		virtual uint32_t* getIndices() { return this->indices; };
		virtual const uint32_t getIndicesSize() { return sizeof( this->indicesSize); };

	protected:
		float* vertices;
		uint32_t verticesSize;
		uint32_t* indices;
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
	public:
		Square()
		{
			// VertexArray
			this->verticesSize = 4 * 3;
			float tempVertices[4*3] = {
				-0.5, -0.5f, 0.0f,
				 0.5, -0.5f, 0.0f,
				 0.5,  0.5f, 0.0f,
				-0.5,  0.5f, 0.0f,
			};
			this->vertices = tempVertices;
			//Index Buffer
			this->indicesSize = 2 * 3;
			uint32_t tempIndices[2*3] = {
				0, 1, 2,
				2, 3, 0,
			};
			this->indices = tempIndices;
		}
	};

	class Cube : public Geometry
	{
	public:
		Cube(glm::vec3 position = { 0.0f, 0.0f, 0.0f })
		{
			// VertexArray
			this->verticesSize = 3 * 8;
			float tempVertices[3 * 8] = {
				-0.5 + position.x, -0.5f + position.y, -0.5f + position.z,
				 0.5 + position.x, -0.5f + position.y, -0.5f + position.z,
				 0.5 + position.x,  0.5f + position.y, -0.5f + position.z,
				-0.5 + position.x,  0.5f + position.y, -0.5f + position.z,

				-0.5 + position.x, -0.5f + position.y,  0.5f + position.z,
				 0.5 + position.x, -0.5f + position.y,  0.5f + position.z,
				 0.5 + position.x,  0.5f + position.y,  0.5f + position.z,
				-0.5 + position.x,  0.5f + position.y,  0.5f + position.z,
			};
			this->vertices = tempVertices;

			//Index Buffer
			this->indicesSize = 12 * 3;
			uint32_t tempIndices[12 * 3] = {
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
			this->indices = tempIndices;
		}
	};
}