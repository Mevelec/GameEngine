#include "hzpch.h"
#include "ITexture.h"

#include "Renderer.h"
#include "Plateform/OpenGl/OpenGLTexture.h"

namespace GameEngine {
	Ref<ITexture2D> ITexture2D::Create(const std::string& path)
	{
		switch (IRenderer::GetAPI())
		{
		case IRendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case IRendererAPI::API::OpengGL:
			return std::make_shared<OpenGLTexture2D>(path);
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
				break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
			return nullptr;
	}
}