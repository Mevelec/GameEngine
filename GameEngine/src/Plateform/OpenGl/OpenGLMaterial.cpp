#include "hzpch.h"

#include "OpenGLMaterial.h"

#include "OpenGLShader.h"
#include <memory>

namespace GameEngine {

	OpenGLMaterial::OpenGLMaterial()
	{
		this->diffuseTex = Texture2D::Create("assets/textures/UV_check.png");
		this->diffuseColor = { 0.f, 1.f, 0.f };
		this->shader = Shader::Create("assets/shaders/default.glsl");
	}

	OpenGLMaterial::~OpenGLMaterial()
	{
	}

	void OpenGLMaterial::bind() const
	{
		//bind textures
		std::dynamic_pointer_cast<OpenGLShader>(this->shader)->bind();

		this->diffuseTex->bind(0);
		std::dynamic_pointer_cast<OpenGLShader>(this->shader)->uploadUniformFloat3("u_Color", this->diffuseColor);

		//this->diffuseTex->bind(1);
		std::dynamic_pointer_cast<OpenGLShader>(this->shader)->uploadUniformFloat3("u_Metal", this->metallicColor);

		//this->diffuseTex->bind(2);
		std::dynamic_pointer_cast<OpenGLShader>(this->shader)->uploadUniformFloat3("u_Specu", this->specularColor);
	}
}