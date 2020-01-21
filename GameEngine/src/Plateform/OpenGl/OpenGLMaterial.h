#pragma once

#include "GameEngine/Renderer/Material/Material.h"

namespace GameEngine {

	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const Ref<Shader>& shader);
		OpenGLMaterial(const std::string& name, const Ref<Shader>& shader);
		virtual ~OpenGLMaterial() override;

		virtual void bind(glm::mat4 viewProjectionMatrix, glm::mat4 transform) const override;

	private:
	};
}
