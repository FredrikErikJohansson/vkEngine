#pragma once

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <iostream>

#include "Window.h"
#include "Device.h"
#include "Validation.h"

class Core
{
public:
	void run();

private:
	VkInstance instance = {};
	Validation validation;
	Window window;
	Device device;

	void initVulkan();
	void mainLoop();
	void cleanup();

	void createInstance();
};

