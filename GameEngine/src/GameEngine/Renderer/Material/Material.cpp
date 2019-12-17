#include "hzpch.h"

#include "Material.h"
#include "../Renderer.h"
#include "Plateform/OpenGl/OpenGLShader.h"

#include <memory>

namespace GameEngine {

	Material::Material()
	{
		this->diffuse = Texture2D::Create("assets/textures/UV_check.png");
		this->diffuseColor = { 1.f, 1.f, 0.f };

		this->shader = Shader::Create("assets/shaders/default.glsl");
	}

	void Material::bind()
	{
		//bind textures
		this->diffuse->bind();
		std::dynamic_pointer_cast<OpenGLShader>(this->shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(this->shader)->uploadUniformFloat3("u_Color", this->diffuseColor);

	}

}
