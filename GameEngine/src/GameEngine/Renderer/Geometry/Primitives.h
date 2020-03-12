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
			//left
				-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			//Right
				-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			//Bottom
				-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				00.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				00.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			//Top
				-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				00.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				00.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			//Front	
				-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				00.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				00.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			//Back
				-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
				00.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
				00.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
				-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
		};

		std::vector<uint32_t> indices = {
			//Left
			0, 1, 2,
			2, 3, 0,
			//Right
			4, 5, 6,
			6, 7, 4,
			//Bottom
			8, 9, 10,
			10, 11, 8,
			//Top
			12, 13, 14, 
			14, 15, 12,
			//Front
			16, 17, 18,
			18, 19, 16,
			//Back
			20, 21, 22,
			22, 23, 20
		};

		StaticGeometry geo(layout, vertices, indices);

		return geo;
	}
	static Geometry CreateCube(Faces faces, glm::fvec3 position, glm::fvec4 color = glm::fvec4(1.0f, 1.0f, 1.0f, 1.0f), float texId = 0.0f) {
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float4, "a_Color"},
			{ GameEngine::ShaderDataType::Float2, "a_TexCoord"},
			{ GameEngine::ShaderDataType::Float, "a_TexId"},
		};

		std::vector<float> vertices;
		std::vector<uint32_t> indices;
		if (faces.left)
		{
			std::vector<float> tmp = {
				//left
					-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
					-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
					-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
					-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			};
			vertices.insert(vertices.end(), tmp.begin(), tmp.end());
			std::vector<uint32_t> tmpI = {
				//Left
				0, 1, 2,
				2, 3, 0,
			};
			indices.insert(indices.end(), tmpI.begin(), tmpI.end());
		}
		if (faces.right)
		{
			std::vector<float> tmp = {
				//Right
					-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
					-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
					-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
					-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			};
			vertices.insert(vertices.end(), tmp.begin(), tmp.end());
			std::vector<uint32_t> tmpI = {
				//Right
				4, 5, 6,
				6, 7, 4,
			};
			indices.insert(indices.end(), tmpI.begin(), tmpI.end());
		}
		if (faces.bottom)
		{
			std::vector<float> tmp = {
				//Bottom
					-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
					00.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
					00.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
					-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			};
			vertices.insert(vertices.end(), tmp.begin(), tmp.end());
			std::vector<uint32_t> tmpI = {
				//Bottom
				8, 9, 10,
				10, 11, 8,
			};
			indices.insert(indices.end(), tmpI.begin(), tmpI.end());
		}
		if (faces.top)
		{
			std::vector<float> tmp = {
				//Top
					-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
					00.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
					00.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
					-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			};
			vertices.insert(vertices.end(), tmp.begin(), tmp.end());
			std::vector<uint32_t> tmpI = {
				//Top
				12, 13, 14,
				14, 15, 12,
			};
			indices.insert(indices.end(), tmpI.begin(), tmpI.end());
		}
		if (faces.front)
		{
			std::vector<float> tmp = {
				//Front	
					-0.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
					00.5f + position.x, -0.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
					00.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
					-0.5f + position.x, 00.5f + position.y, -0.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			};
			vertices.insert(vertices.end(), tmp.begin(), tmp.end());
			std::vector<uint32_t> tmpI = {
				//Front
				16, 17, 18,
				18, 19, 16,
			};
			indices.insert(indices.end(), tmpI.begin(), tmpI.end());
		}
		if (faces.back)
		{
			std::vector<float> tmp = {
				//Back
					-0.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 0.0f, texId,
					00.5f + position.x, -0.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 0.0f, texId,
					00.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 1.0f, 1.0f, texId,
					-0.5f + position.x, 00.5f + position.y, 00.5f + position.z, color.r, color.g, color.b, color.a, 0.0f, 1.0f, texId,
			};
			vertices.insert(vertices.end(), tmp.begin(), tmp.end());
			std::vector<uint32_t> tmpI = {
				//Back
				20, 21, 22,
				22, 23, 20
			};
			indices.insert(indices.end(), tmpI.begin(), tmpI.end());
		}


		StaticGeometry geo(layout, vertices, indices);

		return geo;
	}
}