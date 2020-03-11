#pragma once

#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine {
	

	static Geometry CreateCube(glm::fvec3 position, glm::fvec4 color = glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), float texId = 0.0f) {
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float4, "a_Color"},
			{ GameEngine::ShaderDataType::Float2, "a_TexCoord"},
			{ GameEngine::ShaderDataType::Float, "a_TexId"},
		};

		std::vector<float> vertices = {
			-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				0.5f + position.x, 0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, 0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
				-0.5f + position.x, -0.5f + position.y, 0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				0.5f + position.x, -0.5f + position.y, 0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				0.5f + position.x, 0.5f + position.y, 0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, 0.5f + position.y, 0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
		};

		std::vector<uint32_t> indices = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			4, 0, 3,
			3, 7, 4,

			5, 1, 2,
			2, 6, 5,

			0, 1, 5,
			5, 4, 0,

			3, 2, 6,
			6, 7, 3,
		};

		StaticGeometry geo(layout, vertices, indices);

		return geo;
	}
}