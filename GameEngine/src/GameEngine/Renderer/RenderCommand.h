#pragma once

#include "RendererAPI.h"

namespace GameEngine {

	class RenderCommand {
	public:
		inline static void Init() { rendererAPI->init(); };

		inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { rendererAPI->setViewPort(x, y, width, height); };

		inline static void SetClearColor(const glm::vec4& color) { rendererAPI->setClearColor(color); };
		inline static void Clear() { rendererAPI->clear(); };
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {	rendererAPI->drawIndexed(vertexArray); }

	private:
		static RendererAPI* rendererAPI;
	};
}