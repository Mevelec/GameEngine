#pragma once
#include "hzpch.h"

namespace GameEngine {

	class GraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;

		static Scope<GraphicsContext> Create(void* window);
	};
}