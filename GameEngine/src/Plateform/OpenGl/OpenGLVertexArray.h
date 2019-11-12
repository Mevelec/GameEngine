#pragma once

#include "GameEngine/Renderer/IVertexArray.h"

namespace GameEngine {
	class OpenGLVertexArray : public IVertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer) override;

		virtual std::vector<std::shared_ptr<IVertexBuffer>>& getVertexBuffer() override { return this->vertexBuffers; };
		virtual std::shared_ptr<IIndexBuffer>& getIndexBuffer() override { return this->indexBuffer; };
	private:
		uint32_t rendererID;
		std::vector<std::shared_ptr<IVertexBuffer>> vertexBuffers;
		std::shared_ptr<IIndexBuffer> indexBuffer;
	};
}

