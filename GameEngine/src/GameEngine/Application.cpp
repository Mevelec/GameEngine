#include "hzpch.h"
#include "Application.h"

#include "GameEngine/Log.h"

#include <GLFW/glfw3.h>

namespace GameEngine {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		this->window = std::unique_ptr<IWindow>(IWindow::create());
		this->window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
	}

	Application::~Application()
	{
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
		GE_CORE_TRACE("{0}", e);
	}

	void Application::run()
	{

		while (this->running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			this->window->onUpdate();
		}
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		this->running = false;
		return true;
	}
}