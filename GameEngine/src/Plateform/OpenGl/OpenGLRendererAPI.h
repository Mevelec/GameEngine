#pragma once

#include "GameEngine/Renderer/IRendererAPI.h"

namespace GameEngine {
	class OpenGLRendererAPI : public IRendererAPI
	{
	public:
		virtual void setClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const Ref<IVertexArray>& vertexArray) override;
	};
}


