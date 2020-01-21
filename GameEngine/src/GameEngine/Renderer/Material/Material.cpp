#include "hzpch.h"

#include "Material.h"
#include "../Renderer.h"

#include "Plateform/OpenGl/OpenGLShader.h"
#include "Plateform/OpenGl/OpenGLMaterial.h"

namespace GameEngine {

	Ref<Material> Material::Create(const Ref<Shader>& shader)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpengGL:
			return std::make_shared<OpenGLMaterial>(shader);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<Material> Material::Create(const std::string& name, const Ref<Shader>& shader)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpengGL:
			return std::make_shared<OpenGLMaterial>(name, shader);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}
