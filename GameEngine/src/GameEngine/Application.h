#pragma  once

#include "Core.h"
#include "Events/Event.h"
#include "IWindow.h"

namespace GameEngine
{
	class  GE_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	private:
		std::unique_ptr<IWindow> window;
		bool running = true;
	};

	//To be defined in Client
	Application* CreateApplication();
}
