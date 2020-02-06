#include "hzpch.h"
#include "GameEngine/Renderer/RendererAPI.h"

#include "Plateform/OpenGl/OpenGLRendererAPI.h"

namespace GameEngine {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
			case RendererAPI::API::None:    GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		GE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}