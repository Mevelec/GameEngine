#include "hzpch.h"

#include "Material.h"
#include "../Renderer.h"

#include "Plateform/OpenGl/OpenGLShader.h"


namespace GameEngine {

	Material::Material(const std::string& name, const Ref<Shader>& shader)
		: name(name)
	{
		this->shader = shader;
	}

	Material::Material(const Ref<Shader>& shader)
		: name(shader->getName())
	{
		this->shader = shader;
	}

	Material::~Material()
	{
	}

	void Material::bind(glm::mat4 viewProjectionMatrix, glm::mat4 transform) 
	{
		GE_PROFILE_FUNCTION();

		this->shader->bind();
		this->shader->setMat4("u_ViewProjectionMatrix", viewProjectionMatrix);
		this->shader->setMat4("u_Transform", transform);

		for each (Ref<MaterialComponent> comp in this->components)
		{
			GE_PROFILE_SCOPE("Bind Material Components");

			comp->bind(this->shader);
		}
	}



	template<>
	void MaterialComponentImpl<Ref<Texture>>::bind(const Ref<Shader>& shader)
	{
		this->value->bind(this->slot);
		shader->setInt(this->name, this->slot);
	}
	template<>
	void MaterialComponentImpl<int>::bind(const Ref<Shader>& shader)
	{
		shader->setInt(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<float>::bind(const Ref<Shader>& shader)
	{
		shader->setFloat(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<glm::fvec2>::bind(const Ref<Shader>& shader)
	{
		shader->setFloat2(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<glm::fvec3>::bind(const Ref<Shader>& shader)
	{
		shader->setFloat3(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<glm::fvec4>::bind(const Ref<Shader>& shader)
	{
		shader->setFloat4(this->name, this->value);
	}
	template<>
	void MaterialComponentImpl<glm::fmat4>::bind(const Ref<Shader>& shader)
	{
		shader->setMat4(this->name, this->value);
	}

}
