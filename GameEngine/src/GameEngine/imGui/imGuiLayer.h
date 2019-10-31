#pragma once

#include "GameEngine/Layer/ILayer.h"
#include "GameEngine/Events/MouseEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/ApplicationEvent.h"


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
		bool onMouseMovedEvent(MouseMovedEvent& event);
		bool onMouseScrollEvent(MouseScrollEvent& event);
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);

		bool onKeyPressedEvent(KeyPressedEvent& event);
		bool onKeyReleasedEvent(KeyReleasedEvent& event);

		bool onKeyTypedEvent(KeyTypedEvent& event);
		bool onWindowResizeEvent(WindowResizeEvent& event);
	private:
		float time = 0.0f;
	};
}