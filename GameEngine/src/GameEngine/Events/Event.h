#pragma once
#include "hzpch.h"

#include "GameEngine/Core/Core.h"

namespace GameEngine {
	// Events in GameEngine are currently blocking, meaning when an event occur it
	// immediately gets dispatched and must be dealt with right then and there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the 'event' part of the update stage

	/// Enum of EventTypes
	/// is used to distinct differents events
	/// by filters
	enum  class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		SetedClipboardText,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed,  MouseButtonReleased, MouseMoved, MouseScrolled,
		ChunkDoReload, ChunkSetRenderView
	};

	/// Enum of Events categories
	/// is used to distinct different events
	/// by event source
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
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/// Event class 
	/// used as base for others events
	class Event {
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

		inline const bool isHandled() { return this->handled; }
	protected:
		bool handled = false;
	};

	/// EventDispatcher class 
	class EventDispatcher
	{
	public:
		EventDispatcher(Event & event)
			: event(event)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (this->event.GetEventType() == T::GetStaticType())
			{
				this->event.handled = func(static_cast<T&>(this->event));
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}