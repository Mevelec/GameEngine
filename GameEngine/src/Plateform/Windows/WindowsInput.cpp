#include "hzpch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "GameEngine/Core/Application.h"

namespace GameEngine {

	Scope<Input> Input::instance = CreateScope<WindowsInput>();

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

	std::pair<float, float> WindowsInput::getMouseDeviationImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().GetWindow().getNativeWindow());
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		double posX, posY;
		glfwGetCursorPos(window, &posX, &posY);

		return { (float)width/2 - posX, (float)height/2 - posY };
	}

	void WindowsInput::resetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().GetWindow().getNativeWindow());
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glfwSetCursorPos(window, width / 2, height / 2);
	}

}
