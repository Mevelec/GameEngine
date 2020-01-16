#pragma once

#include "GameEngine/Core/InputControl/Input.h"

namespace GameEngine
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
		virtual std::pair<float, float> getMousePosImpl() override;
		virtual std::pair<float, float> getMouseDeviationImpl() override;
		virtual void resetMousePosImpl() override;
	};
}


