#pragma once

#include "GameEngine/IInput.h"

namespace GameEngine
{
	class WindowsInput : public IInput
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
		virtual std::pair<float, float> getMousePosImpl() override;
	};
}


