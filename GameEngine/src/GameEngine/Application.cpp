#include "hzpch.h"
#include "Application.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Log.h"

namespace GameEngine {
	Application::Application()
	{
		this->window = std::unique_ptr<IWindow>(IWindow::create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{

		while (this->running) {
			this->window->onUpdate();
		}
	}
}