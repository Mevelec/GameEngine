#include "hzpch.h"
#include "Texture.h"

#include "../Renderer.h"
#include "Plateform/OpenGl/OpenGLTexture.h"

namespace GameEngine {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpengGL:
			return std::make_shared<OpenGLTexture2D>(path);
		default:
			GE_CORE_ASSERT(false, "RendererAPI::Unknow renderAPI")
				break;
		}

		GE_CORE_ASSERT(false, "RendererAPI::Something went wrong!")
			return nullptr;
	}
}