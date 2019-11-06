#include "hzpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Plateform/OpenGl/OpenGlBuffer.h"

namespace GameEngine {

	IVertexBuffer* IVertexBuffer::Create(float* vertices, uint32_t size) {
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::None: 
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpengGL:
			return new OpenGlVertexBuffer(vertices, size);
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
			break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
		return nullptr;
	}

	IIndexBuffer* IIndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::OpengGL:
			return new OpenGlIndexBuffer(indices, count);
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
				break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
		return nullptr;
	}

}