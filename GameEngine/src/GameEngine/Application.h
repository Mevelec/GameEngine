#pragma  once

#include "Core.h"

#include "IWindow.h"
#include "GameEngine/Layer/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"



namespace GameEngine
{
	class  GE_API Application
	{
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& e);

		void pushLayer(ILayer* layer);
		void pushOverlay(ILayer* overlay);
	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<IWindow> window;
		bool running = true;
		LayerStack layerStack;
	};

	//To be defined in Client
	Application* CreateApplication();
}
