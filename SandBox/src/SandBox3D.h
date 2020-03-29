#pragma once
#include <GameEngine.h>

#include "ImGui/SandBoxMenu.h"

class SandBox3D : public GameEngine::Layer
{
public:
	GameEngine::ShaderLibrary shaderLib;
	GameEngine::Ref<GameEngine::Material> mat;
	GameEngine::Ref<GameEngine::VertexArray> VA;
public:
	SandBox3D();
	virtual ~SandBox3D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	virtual void onUpdate(GameEngine::TimeStep ts) override;
	virtual void onImGuiRender() override;
	virtual void onEvent(GameEngine::Event& e) override;

	bool onWindowResized(GameEngine::WindowResizeEvent& event);
	bool onKeyPressedEvent(GameEngine::KeyPressedEvent& event);


private:
	GameEngine::Camera* camera;
	float cameraMoveSpeed = 5.0f;
	float cmaraRotateSpeed = 10.0f;
	GameComponents::ChunkManager chunkManager;

	GameEngine::Scope<SandBoxMenu> menu;
};

