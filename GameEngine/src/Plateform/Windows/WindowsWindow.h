#pragma once

#include "GameEngine/Core/Window.h"
#include "GameEngine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace GameEngine {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() { return this->data.width; }
		inline unsigned int getHeight() { return this->data.height; }
		inline virtual void* getNativeWindow() const { return this->window; }
		// Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { this->data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;
	private:
		virtual void init(const WindowProps& props);
		virtual void shutDown();

	private:
		GLFWwindow* window;
		Scope<GraphicsContext> context;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn eventCallback;
		};

		WindowData data;
	};
}