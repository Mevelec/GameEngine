#include "hzpch.h"
#include "Plateform/OpenGl/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace GameEngine {

	static GLenum shaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		GE_CORE_ASSERT(false, "Unknow shader type", type);
		return 0;
	}

	// CONSTRUCTOR/DELETE
	OpenGLShader::OpenGLShader(const std::string&  name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: name(name)
	{
		GE_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;

		this->compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& path)
	{
		GE_PROFILE_FUNCTION();

		std::string source = this->readFile(path);
		auto shaderSources = preProcess(source);

		this->compile(shaderSources);

		//Extract file name from file path
		// assets/shaders/Texture.glsl
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind(".");
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		this->name = name;
	}
	OpenGLShader::OpenGLShader(const std::string& path)
	{
		GE_PROFILE_FUNCTION();

		std::string source = this->readFile(path);
		auto shaderSources = preProcess(source);

		this->compile(shaderSources);

		//Extract file name from file path
		// assets/shaders/Texture.glsl
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind(".");
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		this->name = path.substr(lastSlash, count);
	}

	OpenGLShader::~OpenGLShader()
	{
		GE_PROFILE_FUNCTION();

		glDeleteProgram(rendererID);
	}

	//UTILS
	std::string OpenGLShader::readFile(const std::string& path)
	{
		GE_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				GE_CORE_ERROR("Could not read from file '{0}'", path);
			}
		}
		else
		{
			GE_CORE_ASSERT("Could not open file '{0}'", path);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::preProcess(const std::string& source)
	{
		GE_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTogenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
			GE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTogenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			GE_CORE_ASSERT(shaderTypeFromString(type), "Invalid shader type specified");



			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			GE_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[shaderTypeFromString(type)] = (pos == std::string::npos) ? 
				source.substr(nextLinePos) : 
				source.substr(nextLinePos, pos - nextLinePos);
		}
		return shaderSources;
	}

	void OpenGLShader::compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GE_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		GE_CORE_ASSERT(shaderSources.size() <= 2, "Only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		 
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				GE_CORE_ERROR("{0}", infoLog.data());
				GE_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
			{
				glDetachShader(program, id);
				glDeleteShader(id);
			}

			GE_CORE_ERROR("{0}", infoLog.data());
			GE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		this->rendererID = program;
	}

	// BINDING
	void OpenGLShader::bind() const
	{
		GE_PROFILE_FUNCTION();

		glUseProgram(rendererID);
	}

	void OpenGLShader::unbind() const
	{
		GE_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	// UNIFORMS
	void OpenGLShader::setInt(const std::string& name, int value)
	{
		GE_PROFILE_FUNCTION();

		this->uploadUniformInt(name, value);
	}
	void OpenGLShader::setSampler(const std::string& name, int* value, int size)
	{
		GE_PROFILE_FUNCTION();

		this->uploadUniformSampler(name, value, size);
	}
	void OpenGLShader::setFloat(const std::string& name, const float& value)
	{
		GE_PROFILE_FUNCTION();

		this->uploadUniformFloat(name, value);
	}
	void OpenGLShader::setFloat2(const std::string& name, const glm::vec2& value)
	{
		GE_PROFILE_FUNCTION();

		this->uploadUniformFloat2(name, value);
	}
	void OpenGLShader::setFloat3(const std::string& name, const glm::vec3& value)
	{
		GE_PROFILE_FUNCTION();

		this->uploadUniformFloat3(name, value);
	}
	void OpenGLShader::setFloat4(const std::string& name, const glm::vec4 & value)
	{
		GE_PROFILE_FUNCTION();

		this->uploadUniformFloat4(name, value);
	}
	void OpenGLShader::setMat4(const std::string& name, const glm::mat4 & value)
	{
		GE_PROFILE_FUNCTION();

		this->uploadUniformMat4(name, value);
	}

	uint32_t OpenGLShader::getUniformLocation(const std::string& name)  const
	{
		GE_PROFILE_FUNCTION();

		if (this->uniformLocationCache.find(name) != this->uniformLocationCache.end())
			return this->uniformLocationCache[name];

		GLint location = glGetUniformLocation(this->rendererID, name.c_str());
		if (location == -1)
		{
			GE_CORE_WARN("Uniform '{0}' not found", name);
			return location;
		}

		this->uniformLocationCache[name] = location;
		return location;
	}

	void OpenGLShader::uploadUniformInt(const std::string& name, int value)
	{
		GLint location = getUniformLocation(name);
		glUniform1i(location, value);
	}

	void OpenGLShader::uploadUniformSampler(const std::string& name, int* value, int size)
	{
		GLint location = getUniformLocation(name);
		glUniform1iv(location, size, value);
	}

	void OpenGLShader::uploadUniformFloat(const std::string& name, float value)
	{
		GLint location = getUniformLocation(name);
		glUniform1f(location, value);
	}

	void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = getUniformLocation(name);
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = getUniformLocation(name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = getUniformLocation(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = getUniformLocation(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = getUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}