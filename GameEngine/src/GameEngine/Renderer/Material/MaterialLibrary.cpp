#include "hzpch.h"
#include "MaterialLibrary.h"

namespace GameEngine {
	void MaterialLibrary::add(const Ref<Material>& material)
	{
		auto& name = material->getName();
		GE_CORE_ASSERT(!this->exists(name), "Material already exist");
		this->materials[name] = material;
	}

	void MaterialLibrary::add(const std::string& name, const Ref<Material>& material)
	{
		GE_CORE_ASSERT(!this->exists(name), "Material already exist");
		this->materials[name] = material;
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