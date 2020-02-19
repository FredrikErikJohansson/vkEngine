#pragma once

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Window.h"

class Core
{
public:
	void run();

private:
	VkInstance instance;
	Window window;

	void initVulkan();
	void mainLoop();
	void cleanup();
	void createInstance();
};

