#include "SandBox3D.h"
#include "imgui/imgui.h"

SandBox3D::SandBox3D()
	: Layer("SandBox3D")
	//ocTree(2)
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

	//int a = ocTree.getWidth();
	//
	//for (int x = 0; x <= ocTree.getWidth()-1; x++)
	//{
	//	for (int z = 0; z <= ocTree.getWidth()-1; z++)
	//	{
	//		for (int y = 0; y <= ocTree.getWidth()-1; y++)
	//		{
	//			if(y > ocTree.getWidth()-2)
	//				ocTree.setNode(Blocks::BlockType::Grass, x, y, z, 0);
	//			else
	//				ocTree.setNode(Blocks::BlockType::Dirt, x, y, z, 0);
	//		}
	//	}
	//}
	//ocTree.setNode(Blocks::BlockType::Stone, 0, 0, 0, 0);
	//ocTree.setNode(Blocks::BlockType::Stone, 9, 9, 0, 1);
	//ocTree.setNode(Blocks::BlockType::Dirt, 10, 10, 0, 1);
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
		//int width = ocTree.getWidth()-1;
		//for (int x = 0; x <= width; x++)
		//{
		//	for (int z = 0; z <= width; z++)
		//	{
		//		for (int y = 0; y <= width; y++)
		//		{
		//			Blocks::BlockRegistery::getInstance().renderBlock(
		//				this->ocTree.getNode(x, y, z, 0).data, glm::vec3(x * 2, y * 2, z * 2)
		//			);
		//		}
		//	}
		//}
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