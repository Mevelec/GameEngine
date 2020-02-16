#pragma once

#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine {

	class Square : public Geometry
	{
	private:
		float verticesRef[4 * 3] = {
				-0.5, -0.5f, 0.0f,
				 0.5, -0.5f, 0.0f,
				 0.5,  0.5f, 0.0f,
				-0.5,  0.5f, 0.0f,
		};;
		uint32_t indices[2 * 3] = {
				0, 1, 2,
				2, 3, 0,
		};

		std::vector<float> vertices;

	public:
		Square()
		{
			this->verticesSize = sizeof(this->verticesRef);
			this->indicesSize = sizeof(this->indices);

			this->vertices = std::vector<float>(this->verticesRef, this->verticesRef + this->verticesSize / sizeof(float));
		}

		virtual float* getVertices(glm::vec3 position = glm::vec3(0.0f)) override {
			if (position.x == 0 && position.y == 0 && position.z == 0)
				return this->verticesRef;

			for (int i = 0; i < this->vertices.capacity() - 1; i += 3)
			{
				float a = this->verticesRef[i + 0] + position.x;
				this->vertices.at(i + 0) = this->verticesRef[i + 0] + position.x;
				this->vertices.at(i + 1) = this->verticesRef[i + 1] + position.y;
				this->vertices.at(i + 2) = this->verticesRef[i + 2] + position.z;
			}
			return &this->vertices[0];
		}
		virtual uint32_t * getIndices() override {
			return this->indices;
		}

	};

	class Cube : public Geometry
	{
	private:
		float verticesRef[3 * 8] = {
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

		std::vector<float> vertices;
	public:
		Cube()
		{
			this->verticesSize = sizeof(this->verticesRef);
			this->indicesSize = sizeof(this->indices);

			this->vertices = std::vector<float>(this->verticesRef, this->verticesRef + this->verticesSize / sizeof(float));
		}

		virtual float* getVertices(glm::vec3 position = glm::vec3(0.0f)) override {
			if (position.x == 0 && position.y == 0 && position.z == 0)
				return this->verticesRef;

			for (int i = 0; i < this->vertices.capacity() - 1; i += 3)
			{
				float a = this->verticesRef[i + 0] + position.x;
				this->vertices.at(i + 0) = this->verticesRef[i + 0] + position.x;
				this->vertices.at(i + 1) = this->verticesRef[i + 1] + position.y;
				this->vertices.at(i + 2) = this->verticesRef[i + 2] + position.z;
			}
			return &this->vertices[0];
		}
		virtual uint32_t * getIndices() override {
			return this->indices;
		}
	};
}