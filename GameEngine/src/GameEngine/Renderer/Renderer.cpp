#include "hzpch.h"
#include "Renderer.h"

namespace GameEngine {
	void IRenderer::BeginScene()
	{
	}

	void IRenderer::EndScene()
	{
	}

	void IRenderer::Submit(const std::shared_ptr<IVertexArray>& vertexArray)
	{
		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}