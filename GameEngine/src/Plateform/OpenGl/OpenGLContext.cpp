#include "hzpch.h"
#include "Plateform/OpenGl/OpenGLContext.h"

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
		GE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(this->windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to init GLlad!");

		GE_CORE_INFO("OpenGl Info:");
		GE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		GE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		GE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		#ifdef GE_ENABLE_ASSERTS
				int versionMajor;
				int versionMinor;
				glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
				glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

				GE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "GameEngine requires at least OpenGL version 4.5!");
		#endif

	}

	void OpenGLContext::swapBuffers()
	{
		GE_PROFILE_FUNCTION();

		glfwSwapBuffers(this->windowHandle);
	}
}