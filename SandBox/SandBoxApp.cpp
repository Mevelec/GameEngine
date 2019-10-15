#include <GameEngine.h>

class Sandbox : public GameEngine::Application
{
public:
	Sandbox(){}
	~Sandbox(){}
private:
};

GameEngine::Application* GameEngine::CreateApplication() {
	return new Sandbox();
}