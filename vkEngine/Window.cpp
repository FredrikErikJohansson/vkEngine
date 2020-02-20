#include "Window.h"

void Window::init()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "vkEngine", nullptr, nullptr);
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

const int Window::getWidth() const
{
	return WIDTH;
}

const int Window::getHeight() const
{
	return HEIGHT;
}
