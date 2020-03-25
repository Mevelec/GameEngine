#pragma once
#include "GameEngine/Renderer/Geometry/Geometry.h"

namespace GameEngine
{
	class Loader
	{
	public:
		static GameEngine::Geometry loadOBJ(const char* path);

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
