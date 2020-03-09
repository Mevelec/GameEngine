#pragma once
#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine
{
	class Loader
	{
	public:
		static const bool loadOBJ(const char* path,
			std::vector <float >& out_vertices,
			std::vector < glm::vec2 >& out_uvs,
			std::vector < glm::vec3 >& out_normals,
			std::vector < uint32_t >& out_indices
		);

		// Singleton + constructor
	public:
		static Loader& getInstance()
		{
			static Loader    instance;
			return instance;
		}
	private:
		Loader() {
		}

	public:
		Loader(Loader const&) = delete;
		void operator=(Loader const&) = delete;

	};
}
