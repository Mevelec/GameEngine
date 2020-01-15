#pragma once

#include "GameEngine/Renderer/RendererAPI.h"

namespace GameEngine {
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void init() override;

		virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void setClearColor(const glm::vec4& color) override;
		virtual void clear() override;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}


