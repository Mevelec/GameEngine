#pragma once

#include "RenderCommand.h"
#include "GameEngine/Renderer/Camera/ICamera.h"
#include "GameEngine/Renderer/IShader.h"

namespace GameEngine {

	class IRenderer
	{
	public:
		static void Init();

		static void BeginScene(ICamera& camera);
		static void EndScene();

		static void Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		inline static IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }
	private:
		struct  SceneData
		{
			glm::mat4 viewProjectionMat;
		};

		static SceneData* sceneData;
	};
}