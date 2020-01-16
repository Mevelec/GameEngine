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


private:
	GameEngine::Camera* camera;
	float cameraMoveSpeed = 1.0f;
	float cmaraRotateSpeed = 10.0f;

	GameEngine::Ref<GameEngine::VertexArray> VA;
	GameEngine::Ref<GameEngine::Shader> shader;

	glm::vec3 color = {0.2f, 0.3f, 0.8f };
};

