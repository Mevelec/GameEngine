#pragma once

#include "RenderCommand.h"
#include "GameEngine/Renderer/OrtographicCamera.h"
#include "GameEngine/Renderer/Shader.h"

namespace GameEngine {

	class IRenderer
	{
	public:
		static void BeginScene(OrtographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<IVertexArray>& vertexArray);

		inline static IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }
	private:
		struct  SceneData
		{
			glm::mat4 viewProjectionMat;
		};

		static SceneData* sceneData;
	};
}