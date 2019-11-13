#pragma once

//FOR use by applications

#include "GameEngine/Application.h"
#include "GameEngine/Layer/ILayer.h"
#include "GameEngine/Log.h"

#include "GameEngine/IInput.h"
#include "GameEngine/KeyCodes.h"
#include "GameEngine/MouseButtonCodes.h"

#include "GameEngine/imGui/imGuiLayer.h"

// -- Time -----------------------------
#include "GameEngine/Core/TimeStep.h"

// -- Renderer -------------------------
#include "GameEngine/Renderer/Renderer.h"
#include "GameEngine/Renderer/RenderCommand.h"

#include "GameEngine/Renderer/Buffer.h"
#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/IVertexArray.h"

#include "GameEngine/Renderer/Camera/ICamera.h"
#include "GameEngine/Renderer/Camera/OrtographicCamera.h"
#include "GameEngine/Renderer/Camera/PerspectiveCamera.h"
// -------------------------------------

// --Entry Point -----------------------
#include "GameEngine/EntryPoint.h"
// -------------------------------------