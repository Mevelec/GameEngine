#include "hzpch.h"
#include "GameEngine/Core/Application.h"

#include "GameEngine/Renderer/Renderer.h"

#include "GameEngine/Core/InputControl/Input.h"

#include "GLFW/glfw3.h"

namespace GameEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		GE_PROFILE_FUNCTION();

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
		GE_PROFILE_FUNCTION();

		IRenderer::Shutdown();
	}

	void Application::pushLayer(Layer* layer)
	{
		GE_PROFILE_FUNCTION();

		this->layerStack.pushLayer(layer);
		layer->onAttach();
	}
	void Application::pushOverlay(Layer* overlay)
	{
		GE_PROFILE_FUNCTION();

		this->layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void Application::onEvent(Event& e)
	{
		GE_PROFILE_FUNCTION();

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
		GE_PROFILE_FUNCTION();

		while (this->running) {
			GE_PROFILE_SCOPE("RunLoop");

			float time = glfwGetTime();
			TimeStep timeStep = time - this->lastFrameTime;
			this->lastFrameTime = time;

			if (!this->minimized)
			{
				{
					GE_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : this->layerStack)
					{
						layer->onUpdate(timeStep);
					}
				}

				this->imGuiLayer->begin();
				{
					GE_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : this->layerStack)
					{
						layer->onImGuiRender();
					}
				}
				this->imGuiLayer->end();

			}
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
		GE_PROFILE_FUNCTION();

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
