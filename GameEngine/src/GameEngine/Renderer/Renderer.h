#pragma once

#include "RenderCommand.h"

namespace GameEngine {

	class IRenderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<IVertexArray>& vertexArray);

		inline static IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }
	private:
	};
}