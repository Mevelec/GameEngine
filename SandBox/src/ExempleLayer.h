#pragma once
#include "SandboxApp.h"

class ExampleLayer : public GameEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		int width = GameEngine::Application::get().GetWindow().getWidth();
		int height = GameEngine::Application::get().GetWindow().getHeight();

		this->camera = new GameEngine::PerspectiveCamera(
			70.0f,
			(float)width / (float)height,
			0.01f,
			1000.0f,
			glm::vec3(0, 0, -5)
		);
		//this->camera = new GameEngine::OrtographicCamera( (float)16/ (float)9, { 0, 0, 0 });
	}

	~ExampleLayer() {
		delete this->camera;
	}

	void onUpdate(GameEngine::TimeStep ts)
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

		std::pair<float, float> mousePos = GameEngine::Input::getMouseDeviation();
		//GameEngine::Input::resetMousePos();
		//this->camera->rotate({ this->mouseMoveSpeed * ts * mousePos.second, this->mouseMoveSpeed * ts * mousePos.first, 0 });


		GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GameEngine::RenderCommand::Clear();

		GameEngine::IRenderer::BeginScene(*this->camera);
		{
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(2, 0, 0));
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Sand, glm::vec3(0, 2, 0));
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Grass, glm::vec3(0, 0, 2));/*
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(1, -1, -1));
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(1, -1, -1));
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(-1, 1, -1));
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(-1, 1, 1));
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(1, 1, -1));
			Blocks::BlockRegistery::getInstance().renderBlock(Blocks::BlockType::Dirt, glm::vec3(1, 1, -1));*/


			/*
			for (int x = 0; x < 4; x++)
			{
				for (int y = 0; y < 4; y++)
				{
					for (int z = 0; z < 4; z++)
					{
						this->squareTransform->setPostion(glm::vec3(x, y, z));
						//this->squareTransform->setScale(0.5f);
						GameEngine::IRenderer::Submit(
							flatShader,
							this->vertexArray,
							this->squareTransform->getTransform()
						);
					}
				}
			}
			*/
			// square
			/*
			auto mat = this->materialLib.get("default");
			mat->bind();
			GameEngine::IRenderer::Submit(
				mat->getShader(),
				this->squareVA
				);
			*/
		}
		GameEngine::IRenderer::EndScene();

		// Renderer::Flush();
	}
	void onImGuiRender()
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
	void onEvent(GameEngine::Event& event) override
	{
		GameEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<GameEngine::KeyPressedEvent>(GE_BIND_EVENT_FN(ExampleLayer::onKeyPressedEvent));
		dispatcher.Dispatch<GameEngine::WindowResizeEvent>(GE_BIND_EVENT_FN(ExampleLayer::onWindowResized));
	}

	bool onKeyPressedEvent(GameEngine::KeyPressedEvent& event)
	{
		return false;
	}


	bool onWindowResized(GameEngine::WindowResizeEvent& event)
	{
		this->camera->onWindowResized(event);
		return false;
	}
private:
	GameEngine::Camera* camera;
	float cameraMoveSpeed = 1.0f;
	float cmaraRotateSpeed = 10.0f;
	float mouseMoveSpeed = 1.0f;
};