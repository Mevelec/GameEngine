#include <GameEngine.h>

#include "Plateform/OpenGl/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public GameEngine::ILayer
{
public:
	ExampleLayer() 
		: ILayer("Example")
	{
		int width = GameEngine::Application::get().GetWindow().getWidth();
		int height = GameEngine::Application::get().GetWindow().getHeight();

		this->camera = new GameEngine::PerspectiveCamera(
			70.0f, 
			(float)width / (float)height,
			0.01f, 
			1000.0f
		);
		//this->camera = new GameEngine::OrtographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

		//Vertex Array
		this->vertexArray.reset(GameEngine::IVertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};
		GameEngine::Ref<GameEngine::IVertexBuffer> vertexBuffer;
		vertexBuffer.reset(GameEngine::IVertexBuffer::Create(vertices, sizeof(vertices)));
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float4, "a_Color"},

		};
		vertexBuffer->setLayout(layout);
		this->vertexArray->addVertexBuffer(vertexBuffer);


		//Index Buffer
		unsigned int indices[3] = { 0, 1, 2 };
		GameEngine::Ref<GameEngine::IIndexBuffer> indexBuffer;
		indexBuffer.reset(GameEngine::IIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		this->vertexArray->setIndexBuffer(indexBuffer);

		//////// SQUARE ////////
		//Vertex Array
		this->squareVA.reset(GameEngine::IVertexArray::Create());
		float squareVertices[3 * 4] = {
			 0.75, -0.75f, 0.0f,
			-0.75, -0.75f, 0.0f,
			 0.75,  0.75f, 0.0f,
			-0.75,  0.75f, 0.0f,
		};
		GameEngine::Ref<GameEngine::IVertexBuffer> squareVB;
		squareVB.reset(GameEngine::IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		GameEngine::BufferLayout squareLayout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
		};
		squareVB->setLayout(squareLayout);
		this->squareVA->addVertexBuffer(squareVB);

		//Index Buffer
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 1 };
		GameEngine::Ref<GameEngine::IIndexBuffer> squareIB;
		squareIB.reset(GameEngine::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		this->squareVA->setIndexBuffer(squareIB);

		// BASIC SHADER
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix  * u_Transform * vec4(a_Position, 1.0);
				v_Color = a_Color;
			}			

		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}			

		)";
		this->shader.reset(GameEngine::IShader::Create(vertexSrc, fragmentSrc));

		// FLAT SHADER
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}			

		)";
		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}			

		)";
		this->flatColorShader.reset(GameEngine::IShader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	~ExampleLayer() {
		delete this->camera;
	}

	void onUpdate(GameEngine::TimeStep ts)
	{
		// MOVE
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_A)) {
			this->camera->translate({ this->cameraMoveSpeed * ts , 0, 0});
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_D)) {
			this->camera->translate({ this->cameraMoveSpeed * ts * -1, 0, 0 });
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_W)) {
			this->camera->translate({ 0, 0, this->cameraMoveSpeed * ts });
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_S)) {
			this->camera->translate({ 0, 0, this->cameraMoveSpeed * ts * -1 });
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_LEFT_SHIFT)) {
			this->camera->translate({ 0, this->cameraMoveSpeed * ts, 0 });
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_LEFT_CONTROL)) {
			this->camera->translate({ 0, this->cameraMoveSpeed * ts * -1, 0 });
		}
		// ROTATE
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_Q)) {
			this->camera->rotate({0, this->cmaraRotateSpeed * ts , 0});
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_E)) {
			this->camera->rotate({ 0, this->cmaraRotateSpeed * ts * -1 , 0 });
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_UP)) {
			this->camera->rotate({ this->cmaraRotateSpeed * ts, 0 , 0 });
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_DOWN)) {
			this->camera->rotate({ this->cmaraRotateSpeed * ts * -1, 0 , 0 });
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_LEFT)) {
			this->camera->rotate({ 0, 0, this->cmaraRotateSpeed * ts});
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_RIGHT)) {
			this->camera->rotate({ 0, 0, this->cmaraRotateSpeed * ts * -1 });
		}


		GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GameEngine::RenderCommand::Clear();

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(this->flatColorShader)->bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(this->flatColorShader)->uploadUniformFloat3("u_Color", m_SquareColor);


		GameEngine::IRenderer::BeginScene(*this->camera);
		{
			GameEngine::IRenderer::Submit(this->flatColorShader, this->squareVA);
			GameEngine::IRenderer::Submit(this->shader, this->vertexArray);
		}
		GameEngine::IRenderer::EndScene();

		// Renderer::Flush();
	}
	void onImGuiRender()
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		{
			ImGui::LabelText("", "Camera Position :");
			float camPos[3] = {
				this->camera->getPosition().x,
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
	}

	bool onKeyPressedEvent(GameEngine::KeyPressedEvent& event)
	{
		return false;
	}
private:
	GameEngine::Ref<GameEngine::IShader> shader;
	GameEngine::Ref<GameEngine::IShader> flatColorShader;

	GameEngine::Ref<GameEngine::IVertexArray> vertexArray;
	GameEngine::Ref<GameEngine::IVertexArray> squareVA;

	GameEngine::ICamera* camera;
	float cameraMoveSpeed = 1.0f;
	float cmaraRotateSpeed = 1.0f;

	//GameEngine::Transform squareTrans = GameEngine::Transform();
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};
class Sandbox : public GameEngine::Application
{
public:
	Sandbox(){
		pushLayer(new ExampleLayer());
	}
	~Sandbox(){}
private:
};

GameEngine::Application* GameEngine::CreateApplication() {
	return new Sandbox();
}