#include "hzpch.h"
#include "VertexArray.h"

#include "../Renderer.h"
#include "Plateform/OpenGl/OpenGLVertexArray.h"

namespace GameEngine {

	Ref<VertexArray> VertexArray::Create() {
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpengGL:
			return CreateRef<OpenGLVertexArray>();
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
				break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
		return nullptr;
	}
}