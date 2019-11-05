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

		glGenBuffers(1, &this->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Vertex Buffer
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//Index Buffer
		glGenBuffers(1, &this->indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

			glBindVertexArray(this->vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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