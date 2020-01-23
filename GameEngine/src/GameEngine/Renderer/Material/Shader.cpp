#include "hzpch.h"
#include "Shader.h"

#include "../Renderer.h"
#include "Plateform/OpenGL/OpenGLShader.h"

namespace GameEngine {

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (IRenderer::GetAPI())
		{
			case RendererAPI::API::None:    
				GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpengGL:
				return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& path)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpengGL:
			return CreateRef<OpenGLShader>(name, path);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:
			GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpengGL:
			return CreateRef<OpenGLShader>(path);
		}

		GE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}

namespace GameEngine {
	void ShaderLibrary::add(const Ref<Shader>& shader)
	{
		auto& name = shader->getName();
		GE_CORE_ASSERT(!this->exists(name), "Shader already exist");
		this->shaders[name] = shader;
	}

	void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader)
	{
		GE_CORE_ASSERT(!this->exists(name), "Shader already exist");
		this->shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		this->add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& path)
	{
		auto shader = Shader::Create(path);
		this->add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::get(const std::string& name)
	{
		GE_CORE_ASSERT(this->exists(name), "Shader not found");
		return this->shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name)
	{
		return this->shaders.find(name) != this->shaders.end();
	}
}
