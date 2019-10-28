#pragma  once

#include "Core.h"
#include "Events/Event.h"

namespace GameEngine
{
	class  GE_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	private:

	};

	//To be defined in Client
	Application* CreateApplication();
}
