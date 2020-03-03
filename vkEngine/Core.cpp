#include "Core.h"

void Core::run()
{
	window.init();
	initVulkan();
	mainLoop();
	cleanup();
}

void Core::initVulkan()
{
	createInstance();
	validation.setupDebugMessenger(instance);
	window.createSurface(instance);
	device.pickPhysicalDevice(instance, window.getSurface());
	device.createLogicalDevice(validation.layers, window.getSurface());
	device.createSwapChain(window);
	device.createImageViews();
	pipeline.createRenderPass(device.getDevice(), device.getSwapChainImageFormat());
	pipeline.createGraphicsPipeline(device.getDevice(), device.getSwapChainExtent());
}

void Core::mainLoop()
{
	while (!glfwWindowShouldClose(window.getWindow())) {
		glfwPollEvents();
	}
}

void Core::cleanup()
{
	pipeline.destroy(device.getDevice());
	device.destroy();
	validation.destroy(instance);
	window.destroySurface(instance);
	vkDestroyInstance(instance, nullptr);

	glfwDestroyWindow(window.getWindow());
	glfwTerminate();
}

void Core::createInstance()
{
	if (enableValidationLayers && !validation.checkLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

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

