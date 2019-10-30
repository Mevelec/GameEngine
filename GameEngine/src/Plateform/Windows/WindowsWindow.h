#pragma once

#include "GameEngine/IWindow.h"

#include <GLFW/glfw3.h>

namespace GameEngine {
	class WindowsWindow : public IWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() { return this->data.width; }
		inline unsigned int getHeight() { return this->data.height; }

		// Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { this->data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;
	private:
		virtual void init(const WindowProps& props);
		virtual void shutDown();

	private:
		GLFWwindow* window;

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