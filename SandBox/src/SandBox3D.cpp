#include "SandBox3D.h"

#include <glm/gtc/type_ptr.hpp>
#include "GameEngine/Renderer/Geometry/Loader.h"

SandBox3D::SandBox3D()
	: Layer("SandBox3D")
{
	int width = GameEngine::Application::get().GetWindow().getWidth();
	int height = GameEngine::Application::get().GetWindow().getHeight();

	this->camera = new GameEngine::PerspectiveCamera(
		70.0f,
		(float)width / (float)height,
		0.01f,
		1000.0f,
		glm::vec3(0, 0, -10)
	);

	this->menu = GameEngine::CreateScope<SandBoxMenu>();
	// SHADERS
	this->shaderLib.load("default", "assets/shaders/Default.glsl");
	//mat
	this->mat = GameEngine::MaterialParser::getInstance().loadJson("assets/Materials/sample/configuration.json");

	this->mat = GameEngine::CreateRef<GameEngine::Material>("default", this->shaderLib.get("default"));
	this->mat->addComponent("u_Color", glm::vec4(255, 255, 255, 255) / glm::vec4(255));
	this->mat->addComponent("u_TilingFactor", 1.0f);


	//obj
	auto geo = GameEngine::Loader::loadOBJ("assets/Models/test/box_stack.obj");
	geo.createVA();
	this->VA = geo.getVA();
}

void SandBox3D::onAttach()
{

}

void SandBox3D::onDetach()
{

}

void SandBox3D::onUpdate(GameEngine::TimeStep ts)
{
	GE_PROFILE_FUNCTION();

	// MOVE
	if (GameEngine::Input::IsKeyPressed(GE_KEY_A)) {
		this->camera->translate({ this->cameraMoveSpeed * ts *-1, 0, 0 });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_D)) {
		this->camera->translate({ this->cameraMoveSpeed * ts , 0, 0 });
	}
	if (GameEngine::Input::IsKeyPressed(GE_KEY_W)) {
		this->camera->translate({ 0, 0, this->cameraMoveSpeed * ts });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_S)) {
		this->camera->translate({ 0, 0, this->cameraMoveSpeed * ts * -1 });
	}
	if (GameEngine::Input::IsKeyPressed(GE_KEY_SPACE)) {
		this->camera->translate({ 0, this->cameraMoveSpeed * ts, 0 });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT_CONTROL)) {
		this->camera->translate({ 0, this->cameraMoveSpeed * ts * -1, 0 });
	}

	// ROTATE
	if (GameEngine::Input::IsMouseButtonPressed(GE_MOUSE_BUTTON_3))
	{
		std::pair<float, float> mousePos = GameEngine::Input::getMouseDeviation();
		GameEngine::Input::resetMousePos();
		this->camera->rotate({ 1.0f * ts * mousePos.second, 1.0f * ts * mousePos.first, 0 });
	}

	//Render
	GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GameEngine::RenderCommand::Clear();

	GameEngine::IRenderer::BeginScene(*this->camera);
	{
		GE_PROFILE_SCOPE("Sandbox3D Render");
		this->chunkManager.render();

		GameEngine::IRenderer::Submit(
			this->mat,
			this->VA
		);
	}
	GameEngine::IRenderer::EndScene();
}

void SandBox3D::onEvent(GameEngine::Event& e)
{
	GameEngine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(SandBox3D::onKeyPressedEvent));
	dispatcher.Dispatch<GameEngine::WindowResizeEvent>(GE_BIND_EVENT_FN(SandBox3D::onWindowResized));
	dispatcher.Dispatch<GameEngine::ChunkDoReload>(GE_BIND_EVENT_FN(SandBox3D::onChunkDoReload));
	dispatcher.Dispatch<GameEngine::ChunkSetRenderView>(GE_BIND_EVENT_FN(SandBox3D::onChunkSetRenderView));


}

bool SandBox3D::onKeyPressedEvent(GameEngine::KeyPressedEvent& event)
{
	return false;
}


bool SandBox3D::onWindowResized(GameEngine::WindowResizeEvent& event)
{
	this->camera->onWindowResized(event);
	return false;
}

bool SandBox3D::onChunkDoReload(GameEngine::ChunkDoReload& event)
{
	this->chunkManager.reload();
	return false;
}

bool SandBox3D::onChunkSetRenderView(GameEngine::ChunkSetRenderView& event)
{
	this->chunkManager.setRenderDistance(event.GetValue());
	return false;
}

void SandBox3D::onImGuiRender()
{
	GE_PROFILE_FUNCTION();

	this->menu->render();
}