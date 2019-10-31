#include <GameEngine.h>

class ExampleLayer : public GameEngine::ILayer
{
public:
	ExampleLayer() : ILayer("Example"){}

	void onUpdate()
	{
	}
	void onEvent(GameEngine::Event& event) override
	{
		GE_TRACE("{0}", event);
	}
private:
};
class Sandbox : public GameEngine::Application
{
public:
	Sandbox(){
		pushLayer(new ExampleLayer());
		pushOverlay(new GameEngine::ImGuiLayer());
	}
	~Sandbox(){}
private:
};

GameEngine::Application* GameEngine::CreateApplication() {
	return new Sandbox();
}