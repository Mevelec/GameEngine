#include "hzpch.h"
#include "Renderer.h"

#include "Plateform/OpenGl/OpenGLShader.h"

namespace GameEngine {
	
	IRenderer::SceneData* IRenderer::sceneData = new IRenderer::SceneData;

	void IRenderer::Init()
	{
		RenderCommand::Init();
	}

	void IRenderer::BeginScene(ICamera& camera)
	{
		sceneData->viewProjectionMat = camera.getViewProjectionMat();
	}

	void IRenderer::EndScene()
	{
	}

	void IRenderer::Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_ViewProjectionMatrix", sceneData->viewProjectionMat);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_Transform", transform);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}