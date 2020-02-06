#include "hzpch.h"
#include "Renderer.h"

namespace GameEngine {
	
	Scope<IRenderer::SceneData> IRenderer::sceneData = CreateScope<IRenderer::SceneData>();

	void IRenderer::Init()
	{
		GE_PROFILE_FUNCTION();

		RenderCommand::Init();
	}

	void IRenderer::Shutdown()
	{
		GE_INFO("remember to delete items on  shutdown");
	}

	void IRenderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void IRenderer::BeginScene(Camera& camera)
	{
		GE_PROFILE_FUNCTION();

		sceneData->viewProjectionMat = camera.getViewProjectionMat();
	}

	void IRenderer::EndScene()
	{
		GE_PROFILE_FUNCTION();
	}

	void IRenderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		GE_PROFILE_FUNCTION();

		shader->setMat4("u_ViewProjectionMatrix", sceneData->viewProjectionMat);
		shader->setMat4("u_Transform", transform);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	void IRenderer::Submit(const Ref<Material>& mat, const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		GE_PROFILE_FUNCTION();

		mat->bind(sceneData->viewProjectionMat, transform);

		vertexArray->bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}