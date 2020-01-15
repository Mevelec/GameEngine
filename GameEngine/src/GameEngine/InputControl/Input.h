#pragma once

#include "GameEngine/Core.h"

namespace GameEngine {

	class GE_API Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

	public:
		inline static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		inline static float getMouseX() { return instance->getMouseXImpl(); }
		inline static float getMouseY() { return instance->getMouseYImpl(); }
		inline static std::pair<float, float> getMousePos() { return instance->getMousePosImpl(); }
		inline static std::pair<float, float> getMouseDeviation() { return instance->getMouseDeviationImpl(); }
		inline static void resetMousePos() { instance->resetMousePosImpl(); }

			   		 
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
		virtual std::pair<float, float> getMousePosImpl() = 0;
		virtual std::pair<float, float> getMouseDeviationImpl() = 0;
		virtual void resetMousePosImpl() = 0;


	private:
		static Input* instance;
	};
}