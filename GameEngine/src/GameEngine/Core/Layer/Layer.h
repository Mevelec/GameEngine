#pragma once
#include "GameEngine/Core/Core.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Core/TimeStep.h"

namespace GameEngine {

	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = default;

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate(TimeStep timeStep) {};
		virtual void onImGuiRender() {};
		virtual void onEvent(Event& envent) {};

		inline const std::string getName() { return this->debugName; }
	protected:
		std::string debugName;
	};
}