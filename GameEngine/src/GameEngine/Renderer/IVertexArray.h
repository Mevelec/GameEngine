#pragma once

#include <memory>
#include "GameEngine/Renderer/Buffer.h"

namespace GameEngine {

	class IVertexArray
	{
	public:
		virtual ~IVertexArray() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<IVertexBuffer>>& getVertexBuffer() = 0;
		virtual const std::shared_ptr<IIndexBuffer>& getIndexBuffer() = 0;

		static IVertexArray* Create();
	};
}