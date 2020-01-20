#include "SandboxApp.h"

#include "ExempleLayer.h"

#include "SandBox2D.h"
#include "SandBox3D.h"


#include <GameEngine/Core/EntryPoint.h>




class Sandbox : public GameEngine::Application
{
public:
	Sandbox(){
		//pushLayer(new ExampleLayer());
		pushLayer(new SandBox2D());
		//pushLayer(new SandBox3D());

	}
	~Sandbox(){}
private:
};

GameEngine::Application* GameEngine::CreateApplication() {
	return new Sandbox();
}
