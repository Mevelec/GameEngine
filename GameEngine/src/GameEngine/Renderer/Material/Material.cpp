#include "hzpch.h"

#include "Material.h"
#include "../Renderer.h"

#include "Plateform/OpenGl/OpenGLShader.h"
#include "Plateform/OpenGl/OpenGLMaterial.h"

namespace GameEngine {

	Ref<Material> Material::Create()
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpengGL:
			return std::make_shared<OpenGLMaterial>();
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}
