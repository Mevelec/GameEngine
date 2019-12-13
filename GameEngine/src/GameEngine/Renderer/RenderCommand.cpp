#include "hzpch.h"
#include "RenderCommand.h"

#include "Plateform/OpenGl/OpenGLRendererAPI.h"

namespace GameEngine {
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}