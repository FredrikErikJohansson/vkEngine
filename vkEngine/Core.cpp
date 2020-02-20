#include "Core.h"

void Core::run()
{
	initVulkan();
	mainLoop();
	cleanup();
}

void Core::initVulkan()
{
	createInstance();
	validation.setupDebugMessenger(instance);
	device.pickPhysicalDevice(instance);
	device.createLogicalDevice(validation.layers);
}

void Core::mainLoop()
{
	while (!glfwWindowShouldClose(window.getWindow())) {
		glfwPollEvents();
	}
}

void Core::cleanup()
{
	device.destroy();
	validation.destroy(instance);

	vkDestroyInstance(instance, nullptr);
}

void Core::createInstance()
{
	if (enableValidationLayers && !validation.checkLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "vkEnginer";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = nullptr;
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validation.layers.size());
		createInfo.ppEnabledLayerNames = validation.layers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	uint32_t glfwExtensionCount = 0;
	auto extensions = validation.getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validation.layers.size());
		createInfo.ppEnabledLayerNames = validation.layers.data();

		validation.populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else {
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}
