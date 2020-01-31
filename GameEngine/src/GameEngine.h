#pragma once

//FOR use by applications

#include "GameEngine/Core/Application.h"
#include "GameEngine/Core/Layer/Layer.h"
#include "GameEngine/Core/Log/Log.h"

#include "GameEngine/Core/InputControl/Input.h"
#include "GameEngine/Core/InputControl/KeyCodes.h"
#include "GameEngine/Core/InputControl/MouseButtonCodes.h"

#include "GameEngine/imGui/imGuiLayer.h"

// -- Components -----------------------
#include "GameEngine/Core/Transform/Transform.h"

#include "GameComponents/Blocks/Block.h"
#include "GameComponents/Tiles/Tile.h"

// -- DataStructures
//#include "OcTree.h"

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

#include "GameEngine/Renderer/Material/MaterialLibrary.h"
#include "GameEngine/Renderer/Material/Material.h"

// Camera
#include "GameEngine/Renderer/Camera/Camera.h"
#include "GameEngine/Renderer/Camera/OrtographicCamera.h"
#include "GameEngine/Renderer/Camera/PerspectiveCamera.h"
// -------------------------------------

// --Entry Point -----------------------
//#include "GameEngine/EntryPoint.h"
// -------------------------------------