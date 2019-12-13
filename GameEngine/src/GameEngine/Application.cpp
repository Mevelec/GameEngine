#include "hzpch.h"
#include "Application.h"

#include "GameEngine/Log/Log.h"
#include "GameEngine/Renderer/Renderer.h"

#include "GLFW/glfw3.h"

namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		this->window = std::unique_ptr<Window>(Window::create());
		this->window->setEventCallback(GE_BIND_EVENT_FN(Application::onEvent));

		IRenderer::Init();

		this->imGuiLayer = new ImGuiLayer();
		pushOverlay(this->imGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::pushLayer(Layer* layer)
	{
		this->layerStack.pushLayer(layer);
	}
	void Application::pushOverlay(Layer* overlay)
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

			float time = glfwGetTime();
			TimeStep timeStep = time - this->lastFrameTime;
			this->lastFrameTime = time;

			for (Layer* layer : this->layerStack)
			{
				layer->onUpdate(timeStep);
			}

			this->imGuiLayer->begin();
			for (Layer* layer : this->layerStack)
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
