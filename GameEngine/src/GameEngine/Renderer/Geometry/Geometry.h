#pragma once

#include <glm/glm.hpp>
#include <array>
#include <vector>

#include "GameEngine/Renderer/Buffer/Buffer.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"

namespace GameEngine {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoords;
		float texId;
	};

	class Geometry
	{
	public:
		virtual GameEngine::Ref<GameEngine::VertexArray> getVA() = 0;
		virtual const BufferLayout& getLayout() = 0;

	};

	struct Faces
	{
		bool front = false;
		bool back = false;
		bool bottom = false;
		bool top = false;
		bool left = false;
		bool right = false;
	};

	class FacetedGeometry : Geometry
	{
	public:
		FacetedGeometry(Faces faces);

		virtual const BufferLayout& getLayout() override { return this->layout; };

	private:
		BufferLayout layout;

	};

	class DynamicGeometry : Geometry
	{
	public:
		DynamicGeometry(bool indicesOffset_auto = true);

		void add(float* vertices, const uint32_t countV, const uint32_t* indices, const uint32_t countI);

		void inline setLayout(const BufferLayout& layout) { this->layout = layout; };
		virtual const BufferLayout& getLayout() override { return this->layout; };

		void createVA();

		virtual GameEngine::Ref<GameEngine::VertexArray> getVA() override;

	protected:
		BufferLayout layout;

		GameEngine::Ref<GameEngine::VertexArray> VA;

		bool indicesOffset_auto;

		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		uint32_t verticesOffset = 0;
	};
}