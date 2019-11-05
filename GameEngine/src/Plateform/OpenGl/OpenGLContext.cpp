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

		GE_CORE_INFO("OpenGl Info:");
		GE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(this->windowHandle);
	}
}