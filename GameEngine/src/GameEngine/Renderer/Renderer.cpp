#include "hzpch.h"
#include "Renderer.h"

namespace GameEngine {
	
	IRenderer::SceneData* IRenderer::sceneData = new IRenderer::SceneData;

	void IRenderer::BeginScene(OrtographicCamera& camera)
	{
		sceneData->viewProjectionMat = camera.getViewProjectionMat();
	}

	void IRenderer::EndScene()
	{
	}

	void IRenderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<IVertexArray>& vertexArray)
	{
		shader->bind();
		shader->setUniformMat4("u_ViewProjection", sceneData->viewProjectionMat);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}