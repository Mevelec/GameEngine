#pragma once

#include "GameEngine/Core.h"

namespace GameEngine {

	class GE_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		inline static float getMouseX() { return instance->getMouseXImpl(); }
		inline static float getMouseY() { return instance->getMouseYImpl(); }
		inline static std::pair<float, float> getMousePos() { return instance->getMousePosImpl(); }
			   		 
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
		virtual std::pair<float, float> getMousePosImpl() = 0;

	private:
		static Input* instance;
	};
}