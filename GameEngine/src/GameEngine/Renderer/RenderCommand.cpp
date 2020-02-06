#include "hzpch.h"
#include "GameEngine/Renderer/RenderCommand.h"

#include "Plateform/OpenGl/OpenGLRendererAPI.h"

namespace GameEngine {
	Scope<RendererAPI> RenderCommand::rendererAPI = CreateScope<OpenGLRendererAPI>();
}