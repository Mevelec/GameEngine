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

		virtual void addVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<IVertexBuffer>>& getVertexBuffer() = 0;
		virtual const Ref<IIndexBuffer>& getIndexBuffer() = 0;

		static IVertexArray* Create();
	};
}