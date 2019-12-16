#pragma once

#include <string.h>
#include <unordered_map>

namespace GameEngine {

	class  Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		
		virtual const std::string& getName() const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& path);
	};

	class ShaderLibrary
	{
	public:
		void add(const Ref<Shader>& shader);
		void add(const std::string& name, const Ref<Shader>& shader);

		Ref<Shader> load(const std::string& path);
		Ref<Shader> load(const std::string& name, const std::string& path);

		Ref<Shader> get(const std::string& name);

		bool exists(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> shaders;
	};
}