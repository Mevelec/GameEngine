#pragma once

#include "RenderCommand.h"
#include "GameEngine/Renderer/Camera/Camera.h"
#include "GameEngine/Renderer/Material/Shader.h"

namespace GameEngine {

	class IRenderer
	{
	public:
		static void Init();

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct  SceneData
		{
			glm::mat4 viewProjectionMat;
		};

		static SceneData* sceneData;
	};
}