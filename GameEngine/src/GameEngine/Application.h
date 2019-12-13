#pragma  once

#include "Core.h"

#include "Window.h"
#include "GameEngine/Layer/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Core/TimeStep.h"

#include "GameEngine/imGui/imGuiLayer.h"

namespace GameEngine
{
	class  Application
	{
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline static Application& get() { return *s_Instance; }
		inline Window& GetWindow() { return *this->window;  }
	private:
		bool onWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;
		LayerStack layerStack;
		float lastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//To be defined in Client
	Application* CreateApplication();
}
