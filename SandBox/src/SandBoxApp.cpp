#include <GameEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public GameEngine::ILayer
{
public:
	ExampleLayer() 
		: ILayer("Example")
	{
		int width = GameEngine::Application::get().GetWindow().getWidth();
		int height = GameEngine::Application::get().GetWindow().getHeight();

		this->cameraPos = glm::vec3(0.0f, 0.0f, -0.5f);
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
		std::shared_ptr<GameEngine::IVertexBuffer> vertexBuffer;
		vertexBuffer.reset(GameEngine::IVertexBuffer::Create(vertices, sizeof(vertices)));
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
			{ GameEngine::ShaderDataType::Float4, "a_Color"},

		};
		vertexBuffer->setLayout(layout);
		this->vertexArray->addVertexBuffer(vertexBuffer);


		//Index Buffer
		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<GameEngine::IIndexBuffer> indexBuffer;
		indexBuffer.reset(GameEngine::IIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		this->vertexArray->setIndexBuffer(indexBuffer);

		//////// SQUARE ////////
		this->squareTrans = GameEngine::Transform();
		//Vertex Array
		this->squareVA.reset(GameEngine::IVertexArray::Create());
		float squareVertices[3 * 4] = {
			 0.75, -0.75f, 2.5f,
			-0.75, -0.75f, 2.5f,
			 0.75,  0.75f, 2.5f,
			-0.75,  0.75f, 2.5f,
		};
		std::shared_ptr<GameEngine::IVertexBuffer> squareVB;
		squareVB.reset(GameEngine::IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		GameEngine::BufferLayout squareLayout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position"},
		};
		squareVB->setLayout(squareLayout);
		this->squareVA->addVertexBuffer(squareVB);

		//Index Buffer
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 1 };
		std::shared_ptr<GameEngine::IIndexBuffer> squareIB;
		squareIB.reset(GameEngine::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		this->squareVA->setIndexBuffer(squareIB);

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
		this->shader = std::make_shared<GameEngine::Shader>(vertexSrc, fragmentSrc);

		std::string blueShaderVertexSrc = R"(
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
		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(0.2f, 0.2f, 0.8f, 1.0f);
			}			

		)";


		this->blueShader = std::make_shared<GameEngine::Shader>(blueShaderVertexSrc, blueShaderFragmentSrc);
	}

	~ExampleLayer() {
		delete this->camera;
	}

	void onUpdate(GameEngine::TimeStep ts)
	{
		GE_TRACE("Delta time : {0}s ({1}ms)", ts.getTime(), ts.getMs());

		// MOVE
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_LEFT)) {
			this->cameraPos.x += this->cameraMoveSpeed * ts;
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_RIGHT)) {
			this->cameraPos.x -= this->cameraMoveSpeed * ts;
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_UP)) {
			this->cameraPos.z += this->cameraMoveSpeed * ts;
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_DOWN)) {
			this->cameraPos.z -= this->cameraMoveSpeed * ts;
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_PAGE_UP)) {
			this->cameraPos.y += this->cameraMoveSpeed * ts;
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_PAGE_DOWN)) {
			this->cameraPos.y -= this->cameraMoveSpeed * ts;
		}
		// ROTATE
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_A)) {
			this->cameraRot.y += this->cmaraRotateSpeed * ts;
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_E)) {
			this->cameraRot.y -= this->cmaraRotateSpeed * ts;
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_Z)) {
			this->cameraRot.x += this->cmaraRotateSpeed * ts;
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_S)) {
			this->cameraRot.x -= this->cmaraRotateSpeed * ts;
		}
		if (GameEngine::IInput::IsKeyPressed(GE_KEY_Q)) {
			this->cameraRot.z += this->cmaraRotateSpeed * ts;
		}
		else if (GameEngine::IInput::IsKeyPressed(GE_KEY_D)) {
			this->cameraRot.z -= this->cmaraRotateSpeed * ts;
		}


		GameEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GameEngine::RenderCommand::Clear();

		this->camera->setPostion(this->cameraPos);
		//this->camera->setRotation(this->cameraRot);


		GameEngine::IRenderer::BeginScene(*this->camera);
		{
			GameEngine::IRenderer::Submit(this->blueShader, this->squareVA, this->squareTrans.getTransform());
			this->squareTrans.translate(glm::vec3(0.01f, 0.01f, 0.01f));
			GameEngine::IRenderer::Submit(this->shader, this->vertexArray);
		}
		GameEngine::IRenderer::EndScene();

		// Renderer::Flush();
	}
	void onImGuiRender() 
	{

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
	std::shared_ptr<GameEngine::Shader> shader;
	std::shared_ptr<GameEngine::Shader> blueShader;

	std::shared_ptr<GameEngine::IVertexArray> vertexArray;
	std::shared_ptr<GameEngine::IVertexArray> squareVA;

	GameEngine::PerspectiveCamera* camera;
	glm::vec3 cameraPos;
	glm::vec3 cameraRot;
	float cameraMoveSpeed = 1.0f;
	float cmaraRotateSpeed = 5.0f;

	GameEngine::Transform squareTrans = GameEngine::Transform();

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