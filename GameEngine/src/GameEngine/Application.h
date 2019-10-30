#pragma  once

#include "Core.h"
#include "Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "IWindow.h"

namespace GameEngine
{
	class  GE_API Application
	{
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& e);
	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<IWindow> window;
		bool running = true;
	};

	//To be defined in Client
	Application* CreateApplication();
}
