#pragma once

#include "Shader.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace GameEngine {

	class Material
	{
	public :
		Material(const std::string& name) { this->name = name; };

		virtual ~Material() = default;

		const inline std::string& getName() const { return this->name; };

		const inline Ref<Shader> getShader() { return this->shader; };
		virtual void bind(glm::mat4 viewProjectionMatrix, glm::mat4 transform) const = 0;

		static Ref<Material> Create(const Ref<Shader>& shader);
		static Ref<Material> Create(const std::string& name, const Ref<Shader>& shader);


	protected:
		std::string name;
		Ref<Shader> shader;
	};

	struct  MaterialFlat
	{

	};


}
