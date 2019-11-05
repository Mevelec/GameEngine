#pragma once
#include "hzpch.h"

namespace GameEngine {

	class IGraphicsContext
	{
	public:
		virtual void init() = 0;
		virtual void swapBuffers() = 0;
	};
}