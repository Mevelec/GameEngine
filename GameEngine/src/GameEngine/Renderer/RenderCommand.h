#pragma once

#include "IRendererAPI.h"

namespace GameEngine {

	class RenderCommand {
	public:
		inline static void SetClearColor(const glm::vec4& color) { rendererAPI->setClearColor(color); };
		inline static void Clear() { rendererAPI->clear(); };
		inline static void DrawIndexed(const std::shared_ptr<IVertexArray>& vertexArray) {	rendererAPI->drawIndexed(vertexArray); }

	private:
		static IRendererAPI* rendererAPI;
	};
}