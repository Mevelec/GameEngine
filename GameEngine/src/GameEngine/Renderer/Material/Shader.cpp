#include "hzpch.h"
#include "Shader.h"

#include "../Renderer.h"
#include "Plateform/OpenGL/OpenGLShader.h"

namespace GameEngine {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (IRenderer::GetAPI())
		{
			case RendererAPI::API::None:    
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpengGL:
				return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& path)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpengGL:
			return new OpenGLShader(path);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}