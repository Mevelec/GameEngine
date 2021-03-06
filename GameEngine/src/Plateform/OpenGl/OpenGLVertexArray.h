#pragma once

#include "GameEngine/Renderer/Buffer/VertexArray.h"

namespace GameEngine {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) override;

		virtual std::vector<Ref<IVertexBuffer>>& getVertexBuffer() override { return this->vertexBuffers; };
		virtual Ref<IIndexBuffer>& getIndexBuffer() override { return this->indexBuffer; };
	private:
		uint32_t rendererID;
		uint32_t vertexBufferIndex = 0;
		std::vector<Ref<IVertexBuffer>> vertexBuffers;
		Ref<IIndexBuffer> indexBuffer;
	};
}

