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

		void addVertices(float* vertices, uint32_t size)
		{
			for (uint32_t it = 0; it < size; it += 1)
			{
				this->vertices.push_back(vertices[it]);
			}
			this->update();
		}
		void addIndices(uint32_t* indices, uint32_t size)
		{
			for (uint32_t it = 0; it < size; it += 1)
			{
				this->indices.push_back(indices[it]);
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