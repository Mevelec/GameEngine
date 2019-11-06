#pragma once

namespace GameEngine {

	class IVertexBuffer
	{
	public:
		virtual ~IVertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const  = 0;

		static IVertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IIndexBuffer
	{
	public:
		virtual ~IIndexBuffer() {};

		virtual void bind() const  = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static IIndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}