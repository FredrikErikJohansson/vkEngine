#include "Window.h"

Window::Window()
	: surface{}
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "vkEngine", nullptr, nullptr);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::destroySurface(VkInstance& instance)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}

void Window::createSurface(VkInstance& instance)
{
	if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

GLFWwindow* Window::getWindow() const
{
	return window;
}

VkSurfaceKHR Window::getSurface() const
{
	return surface;
}
