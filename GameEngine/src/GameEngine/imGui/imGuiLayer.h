#pragma once

#include "GameEngine/Core/Layer/Layer.h"
#include "GameEngine/Events/MouseEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/ApplicationEvent.h"


namespace GameEngine {

	class GE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();
	private:
		float time = 0.0f;
	};
}