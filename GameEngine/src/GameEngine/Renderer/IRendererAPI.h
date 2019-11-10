#pragma once

#include "glm.hpp"

#include "GameEngine/Renderer/IVertexArray.h"

namespace GameEngine {

	class IRendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpengGL = 1,
		};
	public:
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const std::shared_ptr<IVertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; };
	private:
		static API s_API;
	};
}