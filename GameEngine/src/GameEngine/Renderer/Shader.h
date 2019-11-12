#pragma once

#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace GameEngine {

	class  Shader
	{
	public:
		 Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~ Shader();

		void bind() const;
		void unbind() const;

		void setUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t rendererID;
	};
}