#pragma once

#include "../Core.h"

#include <string>
#include <functional>

namespace GameEngine {
	// Events in GameEngine are currently blocking, meaning when an event occur it
	// immediately gets dispatched and must be dealt with right then and there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the 'event' part of the update stage

	enum  class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		ApppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed,  MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard      = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4),
	};

// it s a macro create code/line withe parameter types
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class GE_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool>
	public:
		EventDispatcher(Event & event)
			: event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};
}