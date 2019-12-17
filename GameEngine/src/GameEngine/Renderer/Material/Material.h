#pragma once

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace GameEngine {

	class Material
	{
	public :
		virtual ~Material() = default;

		const inline Ref<Shader> getShader() { return this->shader; };
		virtual void bind() const = 0;

		static Ref<Material> Create();

	protected:
		Ref<Shader> shader;

		Ref<GameEngine::Texture> diffuseTex;
		glm::vec3 diffuseColor = { 0.f, 0.f, 0.f };

		Ref<GameEngine::Texture> metallicTex;
		glm::vec3 metallicColor = { 0.f, 0.f, 0.f };

		Ref<GameEngine::Texture> specularTex;
		glm::vec3 specularColor = { 0.5f, 0.5f, 0.5f };

		Ref<GameEngine::Texture> normalTex;		
	};

	class MaterialLibrary
	{
	public:
		void add(const Ref<Material>& shader);
		void add(const std::string& name, const Ref<Material>& shader);

		Ref<Material> get(const std::string& name);

		bool exists(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Material>> shaders;
	};
}
