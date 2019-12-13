#pragma once

#include "GameEngine/Renderer/Buffer/Buffer.h"

namespace GameEngine {

	class OpenGlVertexBuffer : public IVertexBuffer
	{
	public:
		OpenGlVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGlVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return this->layout; }
		virtual void setLayout(const BufferLayout& layout) override { this->layout = layout; }

	private:
		uint32_t rendererID;
		BufferLayout layout;
	};

	class OpenGlIndexBuffer : public IIndexBuffer
	{
	public:
		OpenGlIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGlIndexBuffer();

		virtual uint32_t getCount() const override { return this->count; };

		virtual void bind() const override;
		virtual void unbind() const override;

	private:
		uint32_t rendererID;
		uint32_t count;
	};
}