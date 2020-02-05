#pragma once

#include "hzpch.h"

#include "GameEngine/Core/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "GameEngine",
			unsigned int width = 1920,
			unsigned int height = 720)
			: title(title), width(width), height(height)
		{

		}
	};

	/// class IWindow representing a desktop system based window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth()  = 0;
		virtual unsigned int getHeight() = 0;
		inline virtual void* getNativeWindow()  const = 0;

		// window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Scope<Window> create(const WindowProps& props = WindowProps());

	private:
	};
}