#pragma once
#include <GameEngine.h>

class SandBox2D : public GameEngine::Layer
{
public:
	SandBox2D();
	virtual ~SandBox2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	virtual void onUpdate(GameEngine::TimeStep ts) override;
	virtual void onImGuiRender() override;
	virtual void onEvent(GameEngine::Event& e) override;

	bool onWindowResized(GameEngine::WindowResizeEvent& event);
	bool onKeyPressedEvent(GameEngine::KeyPressedEvent& event);
	bool onMouseScrolled(GameEngine::MouseScrolledEvent& e);


private:
	GameEngine::Camera* camera;
	float cameraMoveSpeed = 1.0f;
	float cmaraRotateSpeed = 10.0f;
};

