#pragma once

#include "GameEngine/Events/Event.h"

namespace GameEngine {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height){}

		unsigned int getWidth(){ return this->width; }
		unsigned int getHeight() { return this->height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << this->width << ", " << this->height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int width, height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};
}