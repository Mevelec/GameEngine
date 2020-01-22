#include "SandBox3D.h"
#include "Blocks/Block.h"
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
		for (int x = 0; x <= 10; x++)
		{
			for (int z = 0; z <= 10; z++)
			{
				for (int y = 0; y <= 10; y++)
				{
					if(y > 6 && y < 10)
						Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(x*2, y*2, z*2));
					else if( y >= 10)
						Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Grass, glm::vec3(x*2, y*2, z*2));
					else
						Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Stone, glm::vec3(x*2, y*2, z*2));
				}
			}
		}
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