#include "SandBox3D.h"
#include "imgui/imgui.h"

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

	int a = chunk.getWidth();
	
	for (int x = 0; x <= chunk.getWidth()-1; x++)
	{
		for (int z = 0; z <= chunk.getWidth()-1; z++)
		{
			for (int y = 0; y <= chunk.getWidth()-1; y++)
			{
				if(y > chunk.getWidth()-2)
					chunk.set(GameComponents::BlockType::Grass, x, y, z);
				else
					chunk.set(GameComponents::BlockType::Dirt, x, y, z);
			}
		}
	}
	//ocTree->set(GameComponents::BlockType::Stone, 0, 0, 0, 0);
	//ocTree->setNode(Blocks::BlockType::Stone, 9, 9, 0, 1);
	//ocTree->setNode(Blocks::BlockType::Dirt, 10, 10, 0, 1);
}

void SandBox3D::onAttach()
{

}

void SandBox3D::onDetach()
{

}

void SandBox3D::onUpdate(GameEngine::TimeStep ts)
{
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
	}
	GameEngine::IRenderer::EndScene();
}

void SandBox3D::onImGuiRender()
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

void SandBox3D::onEvent(GameEngine::Event& e)
{
	GameEngine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(SandBox3D::onKeyPressedEvent));
	dispatcher.Dispatch<GameEngine::WindowResizeEvent>(GE_BIND_EVENT_FN(SandBox3D::onWindowResized));
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