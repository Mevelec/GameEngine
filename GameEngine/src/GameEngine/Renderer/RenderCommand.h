#pragma once

#include "IRendererAPI.h"

namespace GameEngine {

	class RenderCommand {
	public:
		inline static void Init() { rendererAPI->init(); };

		inline static void SetClearColor(const glm::vec4& color) { rendererAPI->setClearColor(color); };
		inline static void Clear() { rendererAPI->clear(); };
		inline static void DrawIndexed(const Ref<IVertexArray>& vertexArray) {	rendererAPI->drawIndexed(vertexArray); }

	private:
		static IRendererAPI* rendererAPI;
	};
}