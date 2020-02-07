#pragma once

#include "GameEngine/Renderer/Buffer/Buffer.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"

namespace GameEngine {

	class Geometry
	{
	public:
		virtual const Ref<VertexArray>& getVertexArray() = 0;

	protected:
		Ref<VertexArray> VA;
	};

	class Square : public Geometry
	{
	public:
		Square()
		{
			// VertexArray
			this->VA = VertexArray::Create();
			float squareVertices[3 * 4] = {
				-0.5, -0.5f, 0.0f,
				 0.5, -0.5f, 0.0f,
				 0.5,  0.5f, 0.0f, 
				-0.5,  0.5f, 0.0f,
			};

			// VertexBuffer
			Ref<IVertexBuffer> VB = GameEngine::IVertexBuffer::Create(squareVertices, sizeof(squareVertices));
			BufferLayout squareLayout = {
				{ GameEngine::ShaderDataType::Float3, "a_Position"},
			};
			VB->setLayout(squareLayout);
			this->VA->addVertexBuffer(VB);

			// IndexBuffer
			//Index Buffer
			unsigned int squareIndices[2 * 3] = {
				0, 1, 2,
				2, 3, 0,
			};
			Ref<IIndexBuffer> IB = IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
			this->VA->setIndexBuffer(IB);
		}

		virtual const Ref<VertexArray>& getVertexArray() override
		{
			return this->VA;
		}
	};

	class Cube : public Geometry
	{
	public:
		Cube()
		{
			// VertexArray
			this->VA = VertexArray::Create();
			float squareVertices[6 * 4] = {
				-0.5, -0.5f, -0.5f,
				 0.5, -0.5f, -0.5f,
				 0.5,  0.5f, -0.5f,
				-0.5,  0.5f, -0.5f,

				-0.5, -0.5f,  0.5f,
				 0.5, -0.5f,  0.5f,
				 0.5,  0.5f,  0.5f,
				-0.5,  0.5f,  0.5f,
			};

			// VertexBuffer
			Ref<IVertexBuffer> VB = GameEngine::IVertexBuffer::Create(squareVertices, sizeof(squareVertices));
			BufferLayout squareLayout = {
				{ GameEngine::ShaderDataType::Float3, "a_Position"},
			};
			VB->setLayout(squareLayout);
			this->VA->addVertexBuffer(VB);

			// IndexBuffer
			//Index Buffer
			unsigned int squareIndices[12 * 3] = {
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
			Ref<IIndexBuffer> IB = IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
			this->VA->setIndexBuffer(IB);
		}

		virtual const Ref<VertexArray>& getVertexArray() override
		{
			return this->VA;
		}
	};
}