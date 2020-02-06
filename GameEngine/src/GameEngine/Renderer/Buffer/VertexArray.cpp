#include "hzpch.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Plateform/OpenGl/OpenGLVertexArray.h"

namespace GameEngine {

	Ref<VertexArray> VertexArray::Create() {
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
				break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
		return nullptr;
	}
}