#pragma once

#include "RendererAPI.h"

namespace GameEngine {

	class RenderCommand {
	public:
		inline static void Init() { rendererAPI->init(); };

		inline static void SetClearColor(const glm::vec4& color) { rendererAPI->setClearColor(color); };
		inline static void Clear() { rendererAPI->clear(); };
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {	rendererAPI->drawIndexed(vertexArray); }

	private:
		static RendererAPI* rendererAPI;
	};
}