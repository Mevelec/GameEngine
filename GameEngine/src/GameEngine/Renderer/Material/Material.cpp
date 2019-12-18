#include "hzpch.h"

#include "Material.h"
#include "../Renderer.h"

#include "Plateform/OpenGl/OpenGLShader.h"
#include "Plateform/OpenGl/OpenGLMaterial.h"

namespace GameEngine {

	Ref<Material> Material::Create(const std::string& name)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); 
			return nullptr;
		case RendererAPI::API::OpengGL:
			return std::make_shared<OpenGLMaterial>(name);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}


namespace GameEngine {
	void MaterialLibrary::add(const Ref<Material>& shader)
	{
		auto& name = shader->getName();
		GE_CORE_ASSERT(!this->exists(name), "Shader already exist");
		this->materials[name] = shader;
	}

	void MaterialLibrary::add(const std::string& name, const Ref<Material>& shader)
	{
		GE_CORE_ASSERT(!this->exists(name), "Shader already exist");
		this->materials[name] = shader;
	}

	Ref<Material> MaterialLibrary::get(const std::string& name)
	{
		GE_CORE_ASSERT(this->exists(name), "Shader not found");
		return this->materials[name];
	}

	bool MaterialLibrary::exists(const std::string& name)
	{
		return this->materials.find(name) != this->materials.end();
	}
}