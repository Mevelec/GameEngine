#pragma once

#include "GameEngine/Renderer/Material/Shader.h"
#include <glm/glm.hpp>

#include <unordered_map>
typedef unsigned int GLenum;

namespace GameEngine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string&  name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);

		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const std::string& getName() const override { return this->name; };

		// SETTERS
		virtual void setInt(const std::string& name, int value) override;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void setMat4(const std::string& name, const glm::mat4& value)   override;

		//UPLOADERS
		void uploadUniformInt(const std::string& name, int value);

		void uploadUniformFloat(const std::string& name, float value);
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t getUniformLocation(const std::string& name) const;
	private:
		std::string readFile(const std::string& path);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
		void compile(const std::unordered_map<GLenum, std::string>& shaderSources);
	private:
		uint32_t rendererID;
		std::string name;

		mutable std::unordered_map<std::string, uint32_t> uniformLocationCache;
	};

}