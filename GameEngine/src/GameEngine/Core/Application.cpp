#include "hzpch.h"
#include "GameEngine/Core/Application.h"

#include "GameEngine/Core/Log/Log.h"
#include "GameEngine/Renderer/Renderer.h"

#include "GameEngine/Core/InputControl/Input.h"

#include "GLFW/glfw3.h"

namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		//PROFILE_SCOPE("GameEngine::OnUpdate");

		GE_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;

		this->window = Window::create();
		this->window->setEventCallback(GE_BIND_EVENT_FN(Application::onEvent));

		IRenderer::Init();

		this->imGuiLayer = new ImGuiLayer();
		pushOverlay(this->imGuiLayer);
	}

	Application::~Application()
	{
		IRenderer::Shutdown();
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
		dispatcher.Dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::onWindowResize));


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

			if (!this->minimized)
			{
				for (Layer* layer : this->layerStack)
				{
					layer->onUpdate(timeStep);
				}
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

	bool Application::onWindowResize(WindowResizeEvent& e)
	{
		if (e.getWidth() == 0 || e.getHeight() == 0)
		{
			this->minimized = true;
			return false;
		}

		this->minimized = false;

		IRenderer::OnWindowResize(e.getWidth(), e.getHeight());

		return false;
	}
}
