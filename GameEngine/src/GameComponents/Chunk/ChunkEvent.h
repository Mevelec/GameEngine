#pragma once
#include "GameEngine/Events/Event.h"

namespace GameEngine {

	class ChunkDoReloadEvent : public Event
	{
	public:
		ChunkDoReloadEvent() = default;

		EVENT_CLASS_TYPE(ChunkDoReload)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};


	class ChunkSetRenderViewEvent : public Event
	{
	public:
		inline int GetValue() const { return distance; }

		EVENT_CLASS_TYPE(ChunkSetRenderView)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		ChunkSetRenderViewEvent(int distance) : distance(distance) {}
	private:
		int distance;
	};

	class ChunkMoveCenterEvent : public Event
	{
	public:
		inline const glm::uvec3& GetValue() const { return center; }

		EVENT_CLASS_TYPE(ChunkLoad)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		ChunkMoveCenterEvent(glm::vec3& center) : center(center) {}
	private:
		const glm::vec3 center;
	};
}