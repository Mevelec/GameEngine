#include "hzpch.h"
#include "IShader.h"

#include "Renderer.h"
#include "Plateform/OpenGL/OpenGLShader.h"

namespace GameEngine {

	IShader* IShader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (IRenderer::GetAPI())
		{
			case IRendererAPI::API::None:    
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case IRendererAPI::API::OpengGL:
				return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}