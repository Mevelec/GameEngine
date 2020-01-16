#include "hzpch.h"
#include "Renderer.h"

#include "Plateform/OpenGl/OpenGLShader.h"

namespace GameEngine {
	
	Scope<IRenderer::SceneData> IRenderer::sceneData = CreateScope<IRenderer::SceneData>();

	void IRenderer::Init()
	{
		RenderCommand::Init();
	}

	void IRenderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void IRenderer::BeginScene(Camera& camera)
	{
		sceneData->viewProjectionMat = camera.getViewProjectionMat();
	}

	void IRenderer::EndScene()
	{
	}

	void IRenderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_ViewProjectionMatrix", sceneData->viewProjectionMat);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_Transform", transform);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}