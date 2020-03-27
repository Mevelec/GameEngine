#pragma once
#include "GameEngine/Events/Event.h"

namespace GameEngine {

	class ChunkDoReload : public Event
	{
	public:
		ChunkDoReload() = default;

		EVENT_CLASS_TYPE(ChunkDoReload)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
	};


	class ChunkSetRenderView : public Event
	{
	public:
		inline int GetValue() const { return distance; }

		EVENT_CLASS_TYPE(ChunkSetRenderView)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		ChunkSetRenderView(int distance) : distance(distance) {}
	private:
		int distance;
	};

	class ChunkLoad : public Event
	{
	public:
		inline const glm::vec3& GetValue() const { return center; }

		EVENT_CLASS_TYPE(ChunkLoad)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		ChunkLoad(glm::vec3& center) : center(center) {}
	private:
		const glm::vec3 center;
	};
}