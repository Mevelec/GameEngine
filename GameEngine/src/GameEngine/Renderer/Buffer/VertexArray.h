#pragma once

#include <memory>
#include "GameEngine/Renderer/Buffer/Buffer.h"

namespace GameEngine {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<IVertexBuffer>>& getVertexBuffer() = 0;
		virtual const Ref<IIndexBuffer>& getIndexBuffer() = 0;

		static VertexArray* Create();
	};
}