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
		DynamicGeometry()
		{
			this->vertices = std::vector<float>();
			this->indices  = std::vector<uint32_t>();

			this->update();
		}

		void update()
		{
			this->verticesSize = sizeof(float) * this->vertices.size();
			this->indicesSize = sizeof(uint32_t) * this->indices.size();
		}

		virtual float* getVertices(glm::vec3 position = glm::vec3(0.0f)) override {
			return &this->vertices[0];
		}
		virtual uint32_t* getIndices() override {
			return &this->indices[0];
		}

		void add(float* vertices, uint32_t sizeV, uint32_t* indices, uint32_t sizeI)
		{

			int offsetI = this->verticesSize / sizeof(float) / 3;
			for (uint32_t it = 0; it < sizeI; it += 1)
			{
				this->indices.push_back(indices[it] + offsetI);
			}

			for (uint32_t it = 0; it < sizeV; it += 1)
			{
				this->vertices.push_back(vertices[it]);
			}

			this->update();
		}

		void createVA()
		{
			GameEngine::Ref<GameEngine::IVertexBuffer> VB = GameEngine::IVertexBuffer::Create(this->getVertices(), this->getVerticesSize());
			GameEngine::BufferLayout squareLayout = {
				{ GameEngine::ShaderDataType::Float3, "a_Position"},
			};
			VB->setLayout(squareLayout);

			this->VA = GameEngine::VertexArray::Create();
			this->VA->addVertexBuffer(VB);

			GameEngine::Ref<GameEngine::IIndexBuffer> IB = GameEngine::IIndexBuffer::Create(this->getIndices(), this->getIndicesSize() / sizeof(uint32_t));
			this->VA->setIndexBuffer(IB);
		}

		GameEngine::Ref<GameEngine::VertexArray> getVA() { return this->VA; }

	protected:
		bool toGenerate = false;
		GameEngine::Ref<GameEngine::VertexArray> VA;

		std::vector<float> vertices;
		std::vector<uint32_t> indices;
	};

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
		virtual uint32_t* getIndices() override {
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

			for (int i = 0; i < this->vertices.capacity()-1; i += 3)
			{
				float a = this->verticesRef[i + 0] + position.x;
				this->vertices.at(i + 0) = this->verticesRef[i + 0] + position.x;
				this->vertices.at(i + 1) = this->verticesRef[i + 1] + position.y;
				this->vertices.at(i + 2) = this->verticesRef[i + 2] + position.z;
			}
			return &this->vertices[0];
		}
		virtual uint32_t* getIndices() override {
			return this->indices;
		}
	};
}