#pragma once

#include "GameEngine/Layer/ILayer.h"
namespace GameEngine {

	class GE_API ImGuiLayer : public ILayer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event& event);
	private:
		float time = 0.0f;
	};
}