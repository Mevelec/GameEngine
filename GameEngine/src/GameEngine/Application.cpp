#include "hzpch.h"
#include "Application.h"

#include "GameEngine/Log.h"
#include "GameEngine/Renderer/Renderer.h"

namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: camera(-1.0f, 1.0f, -1.0f, 1.0f)
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		this->window = std::unique_ptr<IWindow>(IWindow::create());
		this->window->setEventCallback(GE_BIND_EVENT_FN(Application::onEvent));

		this->imGuiLayer = new ImGuiLayer();
		pushOverlay(this->imGuiLayer);

		//Vertex Array
		this->vertexArray.reset(IVertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};
		std::shared_ptr<IVertexBuffer> vertexBuffer;
		vertexBuffer.reset(IVertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},

		};
		vertexBuffer->setLayout(layout);
		this->vertexArray->addVertexBuffer(vertexBuffer);


		//Index Buffer
		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IIndexBuffer> indexBuffer;
		indexBuffer.reset(IIndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		this->vertexArray->setIndexBuffer(indexBuffer);
		
		//////// SQUARE ////////
		//Vertex Array
		this->squareVA.reset(IVertexArray::Create());
		float squareVertices[3 * 4] = {
			 0.75, -0.75f, 0.0f,
			-0.75, -0.75f, 0.0f,
			 0.75,  0.75f, 0.0f,
			-0.75,  0.75f, 0.0f,
		};
		std::shared_ptr<IVertexBuffer> squareVB;
		squareVB.reset(IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "a_Position"},
		};
		squareVB->setLayout(squareLayout);
		this->squareVA->addVertexBuffer(squareVB);

		//Index Buffer
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 1};
		std::shared_ptr<IIndexBuffer> squareIB;
		squareIB.reset(IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		this->squareVA->setIndexBuffer(squareIB);
		
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
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
		this->shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
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


		this->blueShader = std::make_shared<Shader>(blueShaderVertexSrc, blueShaderFragmentSrc);
	}

	void Application::pushLayer(ILayer* layer)
	{
		this->layerStack.pushLayer(layer);
	}
	void Application::pushOverlay(ILayer* overlay)
	{
		this->layerStack.pushOverlay(overlay);
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = this->layerStack.end(); it != this->layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.isHandled())
				break;
		}
	}

	void Application::run()
	{

		while (this->running) {

			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			IRenderer::BeginScene();
			{
				this->blueShader->bind();
				IRenderer::Submit(this->squareVA);
				this->shader->bind();
				IRenderer::Submit(this->vertexArray);
			}
			IRenderer::EndScene();

			// Renderer::Flush();

			for (ILayer* layer : this->layerStack) 
			{
				layer->onUpdate();
			}

			this->imGuiLayer->begin();
			for (ILayer* layer : this->layerStack)
			{
				layer->onImGuiRender();
			}
			this->imGuiLayer->end();


			this->window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		this->running = false;
		return true;
	}
}
