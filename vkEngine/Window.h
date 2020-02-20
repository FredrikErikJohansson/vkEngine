#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();

	GLFWwindow* getWindow() const;

private:
	GLFWwindow* window;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
};

