#pragma  once

#include "Core.h"

#include "IWindow.h"
#include "GameEngine/Layer/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/imGui/imGuiLayer.h"

#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Buffer.h"
#include "GameEngine/Renderer/IVertexArray.h"
#include "GameEngine/Renderer/OrtographicCamera.h"


namespace GameEngine
{
	class  GE_API Application
	{
	public:
		Application();
		~Application() = default;

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

		std::shared_ptr<Shader> shader;
		std::shared_ptr<Shader> blueShader;

		std::shared_ptr<IVertexArray> vertexArray;
		std::shared_ptr<IVertexArray> squareVA;

		OrtographicCamera camera;
	private:
		static Application* s_Instance;
	};

	//To be defined in Client
	Application* CreateApplication();
}
