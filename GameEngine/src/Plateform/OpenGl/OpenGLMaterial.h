#pragma once

#include "GameEngine/Renderer/Material/Material.h"

namespace GameEngine {

	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const std::string& name);
		virtual ~OpenGLMaterial() override;

		virtual void bind() const override;

	private:
	};
}
