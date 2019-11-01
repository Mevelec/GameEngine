#include "hzpch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "GameEngine/Application.h"

namespace GameEngine {

	IInput* IInput::instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().GetWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().GetWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::getMouseXImpl()
	{
		auto [x, y] = this->getMousePosImpl();
		return x;
	}

	float WindowsInput::getMouseYImpl()
	{
		auto [x, y] = this->getMousePosImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::getMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().GetWindow().getNativeWindow());
		double posX, posY;
		glfwGetCursorPos(window, &posX, &posY);

		return { (float)posX, (float)posY };
	}

}
