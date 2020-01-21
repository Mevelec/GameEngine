#pragma once

#include "RenderCommand.h"
#include "GameEngine/Renderer/Camera/Camera.h"
#include "GameEngine/Renderer/Material/Shader.h"

namespace GameEngine {

	class IRenderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));
		static void IRenderer::SubmitQuad(const Ref<Shader>& shader, const glm::vec3& positionr, const glm::vec3& size, const glm::vec4& color);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct  SceneData
		{
			glm::mat4 viewProjectionMat;
		};

		static Scope<SceneData> sceneData;
	};
}