#pragma once

#include "Event.h"

namespace GameEngine {

	class GE_API WindowResizeEvent : public Event
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

	class GE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};

	class GE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent(){}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};

	class GE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};

	class GE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};
}