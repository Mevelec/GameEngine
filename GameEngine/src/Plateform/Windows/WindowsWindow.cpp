#include "hzpch.h"
#include "WindowsWindow.h"

namespace GameEngine {
	static bool s_GLFWInitialized = false;

	IWindow* IWindow::create(const WindowProps& props) {
		return new WindowsWindow(props);
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

		GE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTermibate on system shutdown
			int succes = glfwInit();
			GE_CORE_ASSERT(succes, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		this->window = glfwCreateWindow(this->data.width, this->data.height, this->data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(this->window);
		glfwSetWindowUserPointer(this->window, &this->data);
		this->setVSync(true);
	}

	void WindowsWindow::shutDown() {
		glfwDestroyWindow(this->window);
	}

	void WindowsWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(this->window);
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