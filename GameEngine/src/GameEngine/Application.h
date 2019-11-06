#pragma  once

#include "Core.h"

#include "IWindow.h"
#include "GameEngine/Layer/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/imGui/imGuiLayer.h"

#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Buffer.h"

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

		inline static Application& get() { return *s_Instance; }
		inline IWindow& GetWindow() { return *this->window;  }
	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<IWindow> window;
		ImGuiLayer* imGuiLayer;
		bool running = true;
		LayerStack layerStack;

		unsigned int vertexArray;

		std::unique_ptr<Shader> shader;
		std::unique_ptr<IVertexBuffer> vertexBuffer;
		std::unique_ptr<IIndexBuffer> indexBuffer;

	private:
		static Application* s_Instance;
	};

	//To be defined in Client
	Application* CreateApplication();
}
