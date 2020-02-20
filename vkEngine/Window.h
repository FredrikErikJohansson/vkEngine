#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

class Window
{
public:
	Window();
	~Window();

	void destroySurface(VkInstance& instance);
	void createSurface(VkInstance& instance);
	GLFWwindow* getWindow() const;
	VkSurfaceKHR getSurface() const;

private:
	GLFWwindow* window;
	VkSurfaceKHR surface;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
};

