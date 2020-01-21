#include "hzpch.h"

#include "OpenGLMaterial.h"

#include "OpenGLShader.h"
#include <memory>

namespace GameEngine {

	OpenGLMaterial::OpenGLMaterial(const std::string& name, const Ref<Shader>& shader)
		: Material(name)
	{
		this->shader = shader;
	}

	OpenGLMaterial::OpenGLMaterial(const Ref<Shader>& shader)
		: Material(shader->getName())
	{
		this->shader = shader;
	}

	OpenGLMaterial::~OpenGLMaterial()
	{
	}

	void OpenGLMaterial::bind(glm::mat4 viewProjectionMatrix, glm::mat4 transform) const
	{
		this->shader->bind();
		this->shader->setMat4("u_ViewProjectionMatrix", viewProjectionMatrix);
		this->shader->setMat4("u_Transform", transform);
		this->shader->setFloat3("u_Color", glm::vec3(1, 0, 0)/*this->diffuseColor*/);
	}
}