#include "hzpch.h"
#include "GameEngine/Renderer/Buffer/Buffer.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Plateform/OpenGl/OpenGlBuffer.h"

namespace GameEngine {

	Ref<IVertexBuffer> IVertexBuffer::Create(float* vertices, uint32_t size) {
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGlVertexBuffer>(vertices, size);
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
			break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
		return nullptr;
	}

	Ref<IIndexBuffer> IIndexBuffer::Create(uint32_t* indices, uint32_t count) {
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGlIndexBuffer>(indices, count);
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
				break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
		return nullptr;
	}

}