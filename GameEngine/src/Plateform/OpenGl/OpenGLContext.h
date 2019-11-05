#pragma once

#include "GameEngine/Renderer/IGraphicsContext.h"

struct GLFWwindow;

namespace GameEngine {

	class  OpenGLContext : public IGraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}