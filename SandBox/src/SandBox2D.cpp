#include "SandBox2D.h"
#include "Tiles/Tile.h"
#include "imgui/imgui.h"


SandBox2D::SandBox2D()
	: Layer("SandBox2D")
{
	int width = GameEngine::Application::get().GetWindow().getWidth();
	int height = GameEngine::Application::get().GetWindow().getHeight();

	this->camera = new GameEngine::OrtographicCamera( (float)width / (float)height, { 0, 0, -50 });
}

void SandBox2D::onAttach()
{

}

void SandBox2D::onDetach()
{

}

void SandBox2D::onUpdate(GameEngine::TimeStep ts)
{
	// MOVE
	if (GameEngine::Input::IsKeyPressed(GE_KEY_A)) {
		this->camera->translate({ this->cameraMoveSpeed * ts, 0, 0 });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_D)) {
		this->camera->translate({ this->cameraMoveSpeed * ts * -1 , 0, 0 });
	}
	if (GameEngine::Input::IsKeyPressed(GE_KEY_W)) {
		this->camera->translate({ 0, 0, this->cameraMoveSpeed * ts });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_S)) {
		this->camera->translate({ 0, 0, this->cameraMoveSpeed * ts * -1 });
	}
	if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT_SHIFT)) {
		this->camera->translate({ 0, this->cameraMoveSpeed * ts, 0 });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT_CONTROL)) {
		this->camera->translate({ 0, this->cameraMoveSpeed * ts * -1, 0 });
	}
	// ROTATE
	if (GameEngine::Input::IsKeyPressed(GE_KEY_Q)) {
		this->camera->rotate({ 0, this->cmaraRotateSpeed * ts , 0 });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_E)) {
		this->camera->rotate({ 0, this->cmaraRotateSpeed * ts * -1 , 0 });
	}
	if (GameEngine::Input::IsKeyPressed(GE_KEY_UP)) {
		this->camera->rotate({ this->cmaraRotateSpeed * ts, 0 , 0 });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_DOWN)) {
		this->camera->rotate({ this->cmaraRotateSpeed * ts * -1, 0 , 0 });
	}
	if (GameEngine::Input::IsKeyPressed(GE_KEY_LEFT)) {
		this->camera->rotate({ 0, 0, this->cmaraRotateSpeed * ts });
	}
	else if (GameEngine::Input::IsKeyPressed(GE_KEY_RIGHT)) {
		this->camera->rotate({ 0, 0, this->cmaraRotateSpeed * ts * -1 });
	}

	//Render
	GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GameEngine::RenderCommand::Clear();

	GameEngine::IRenderer::BeginScene(*this->camera);
	{
		Tiles::TilesRegistery::getInstance().renderTile(Tiles::TilesType::Dirt, glm::vec3(2, 0, 0));
		Tiles::TilesRegistery::getInstance().renderTile(Tiles::TilesType::Sand, glm::vec3(0, 2, 0));

		Tiles::TilesRegistery::getInstance().renderTile(Tiles::TilesType::Grass, glm::vec3(0, 0, 2));
		Tiles::TilesRegistery::getInstance().renderTile(Tiles::TilesType::Grass, glm::vec3(2, 2, 0));

	}
	GameEngine::IRenderer::EndScene();
}

void SandBox2D::onImGuiRender()
{
	ImGui::Begin("Settings");
	{
		ImGui::LabelText("", "Camera Position :");
		float camPos[3] = {
			this->camera->getPosition().x * -1,
			this->camera->getPosition().y,
			this->camera->getPosition().z
		};
		ImGui::DragFloat3("X Y Z",
			camPos
		);

		ImGui::LabelText("", "Camera Rotation Degrees :");
		float camRotDegree[3] = {
			this->camera->getRotation().x,
			this->camera->getRotation().y,
			this->camera->getRotation().z
		};
		ImGui::DragFloat3("X Y Z",
			camRotDegree
		);

		ImGui::LabelText("", "Camera Rotation Radians :");
		float camRotRadians[3] = {
			this->camera->getEulerAngles().x,
			this->camera->getEulerAngles().y,
			this->camera->getEulerAngles().z
		};
		ImGui::DragFloat3("X Y Z",
			camRotRadians
		);

		ImGui::LabelText("", "Camera Rotation Degrees :");
		float camRotQuat[4] = {
			this->camera->getQuaternions().x,
			this->camera->getQuaternions().y,
			this->camera->getQuaternions().z,
			this->camera->getQuaternions().w
		};
		ImGui::DragFloat4("X Y Z W",
			camRotQuat
		);
	}

	ImGui::End();
}

void SandBox2D::onEvent(GameEngine::Event& e)
{
	GameEngine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(SandBox2D::onKeyPressedEvent));
	dispatcher.Dispatch<GameEngine::WindowResizeEvent>(GE_BIND_EVENT_FN(SandBox2D::onWindowResized));
	dispatcher.Dispatch<GameEngine::MouseScrolledEvent>(GE_BIND_EVENT_FN(SandBox2D::onMouseScrolled));

}

bool SandBox2D::onKeyPressedEvent(GameEngine::KeyPressedEvent& event)
{
	return false;
}

bool SandBox2D::onMouseScrolled(GameEngine::MouseScrolledEvent& e)
{
	this->camera->zoom(e.GetOffsetY() * 0.25f * -1);
	
	return false;
}

bool SandBox2D::onWindowResized(GameEngine::WindowResizeEvent& event)
{
	this->camera->onWindowResized(event);
	return false;
}