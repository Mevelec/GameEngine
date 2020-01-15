#pragma once

//FOR use by applications

#include "GameEngine/Application.h"
#include "GameEngine/Layer/Layer.h"
#include "GameEngine/Log/Log.h"

#include "GameEngine/InputControl/Input.h"
#include "GameEngine/InputControl/KeyCodes.h"
#include "GameEngine/InputControl/MouseButtonCodes.h"

#include "GameEngine/imGui/imGuiLayer.h"

// -- Components -----------------------
#include "GameEngine/GameComponents/Transform.h"
// -- Time -----------------------------
#include "GameEngine/Core/TimeStep.h"

// -- Renderer -------------------------
#include "GameEngine/Renderer/Renderer.h"
#include "GameEngine/Renderer/RenderCommand.h"

#include "GameEngine/Renderer/Buffer/Buffer.h"
#include "GameEngine/Renderer/Buffer/VertexArray.h"

// Texture
#include "GameEngine/Renderer/Material/Shader.h"
#include "GameEngine/Renderer/Material/Texture.h"
#include "GameEngine/Renderer/Material/Material.h"

// Camera
#include "GameEngine/Renderer/Camera/Camera.h"
#include "GameEngine/Renderer/Camera/OrtographicCamera.h"
#include "GameEngine/Renderer/Camera/PerspectiveCamera.h"
// -------------------------------------

// --Entry Point -----------------------
//#include "GameEngine/EntryPoint.h"
// -------------------------------------