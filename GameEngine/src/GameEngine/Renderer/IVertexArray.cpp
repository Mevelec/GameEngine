#include "hzpch.h"
#include "IVertexArray.h"

#include "Renderer.h"
#include "Plateform/OpenGl/OpenGLVertexArray.h"

namespace GameEngine {

	IVertexArray* IVertexArray::Create() {
		switch (IRenderer::GetAPI())
		{
		case IRendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case IRendererAPI::API::OpengGL:
			return new OpenGLVertexArray();
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
				break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
		return nullptr;
	}
}