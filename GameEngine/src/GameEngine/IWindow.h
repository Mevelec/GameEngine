#pragma once

#include "hzpch.h"

#include "Core.h"
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
	class GE_API IWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~IWindow() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth()  = 0;
		virtual unsigned int getHeight() = 0;

		// window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static IWindow* create(const WindowProps& props = WindowProps());

	private:
	};
}