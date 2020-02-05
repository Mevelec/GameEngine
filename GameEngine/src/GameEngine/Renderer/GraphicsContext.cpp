#include "hzpch.h"
#include "GameEngine/Renderer/GraphicsContext.h"

#include "GameEngine/Renderer/Renderer.h"
#include "Plateform/OpenGl/OpenGLContext.h"

namespace GameEngine {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (IRenderer::GetAPI())
		{
		case RendererAPI::API::None:    GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}