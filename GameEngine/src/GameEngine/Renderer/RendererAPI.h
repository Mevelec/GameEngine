#pragma once

#include <glm/glm.hpp>

#include "GameEngine/Renderer/Buffer/VertexArray.h"

namespace GameEngine {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpengGL = 1,
		};
	public:
		virtual void init() = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void clear() = 0;

		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; };
	private:
		static API s_API;
	};
}