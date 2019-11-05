#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace GameEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: windowHandle(windowHandle)
	{
		GE_CORE_ASSERT(windowHandle, "windowHandle is null!");

	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(this->windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to init GLlad!");
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(this->windowHandle);
	}
}