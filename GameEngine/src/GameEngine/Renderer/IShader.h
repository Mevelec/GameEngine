#pragma once

#include <string.h>

namespace GameEngine {

	class  IShader
	{
	public:
		virtual ~IShader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		
		static IShader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}