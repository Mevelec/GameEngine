#include "hzpch.h"
#include "Plateform/Windows/WindowsWindow.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/MouseEvent.h"
#include "GameEngine/Events/KeyEvent.h"

#include "Plateform/OpenGl/OpenGLContext.h"

namespace GameEngine {
	static uint8_t GLFWWindowCount = 0;

	static void GLFWErrorCallBack(int error, const char* description)
	{
		GE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Scope<Window> Window::create(const WindowProps& props) {
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		this->shutDown();
	}

	void WindowsWindow::init(const WindowProps& props) {
		this->data.title = props.title;
		this->data.width = props.width;
		this->data.height = props.height;

		GE_CORE_INFO("Creating window '{0}' ({1}, {2})", props.title, props.width, props.height);

		if (GLFWWindowCount == 0)
		{
			int succes = glfwInit();
			GE_CORE_ASSERT(succes, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallBack);
		}

		this->window = glfwCreateWindow(this->data.width, this->data.height, this->data.title.c_str(), nullptr, nullptr);
		GLFWWindowCount++;

		this->context = GraphicsContext::Create(window);
		this->context->init();

		glfwSetWindowUserPointer(this->window, &this->data);
		this->setVSync(true);

		//set GLFW callbacks
		glfwSetWindowSizeCallback(this->window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			}
		);

		glfwSetWindowCloseCallback(this->window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallback(event);
			}
		);

		glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
				}
			}
		);

		glfwSetCharCallback(this->window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.eventCallback(event);
			}
		);
		glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}					
				}
			}
		);

		glfwSetScrollCallback(this->window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			}
		);

		glfwSetCursorPosCallback(this->window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallback(event);
			}
		);
	}

	void WindowsWindow::shutDown() {
		glfwDestroyWindow(this->window);
		--GLFWWindowCount;
		if (GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::onUpdate() {
		glfwPollEvents();

		this->context->swapBuffers();
	}

	void WindowsWindow::setVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		this->data.VSync = enabled;
	}

	bool WindowsWindow::isVSync() const {
		return this->data.VSync;
	}
}