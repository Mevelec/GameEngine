#pragma once
#include "GameEngine/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {

	class GE_API ILayer
	{
	public:
		ILayer(const std::string& debugName = "Layer");
		virtual ~ILayer();

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate() {};
		virtual void onImGuiRender() {};
		virtual void onEvent(Event& envent) {};

		inline const std::string getName() { return this->debugName; }
	protected:
		std::string debugName;
	};
}