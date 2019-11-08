#include "hzpch.h"
#include "RenderCommand.h"

#include "Plateform/OpenGl/OpenGLRendererAPI.h"

namespace GameEngine {
	IRendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}