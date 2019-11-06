#include "hzpch.h"
#include "Application.h"

#include "GameEngine/Log.h"

#include <glad/glad.h>

namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		this->window = std::unique_ptr<IWindow>(IWindow::create());
		this->window->setEventCallback(GE_BIND_EVENT_FN(Application::onEvent));

		this->imGuiLayer = new ImGuiLayer();
		pushOverlay(this->imGuiLayer);

		//Vertex Array

		glGenVertexArrays(1, &this->vertexArray);
		glBindVertexArray(this->vertexArray);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		this->vertexBuffer = std::unique_ptr<IVertexBuffer>(IVertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//Index Buffer
		unsigned int indices[3] = { 0, 1, 2 };
		this->indexBuffer = std::unique_ptr<IIndexBuffer>(IIndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}			

		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}			

		)";


		this->shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
	}
	Application::~Application()
	{
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			this->shader->bind();
			glBindVertexArray(this->vertexArray);
			glDrawElements(GL_TRIANGLES, this->indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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