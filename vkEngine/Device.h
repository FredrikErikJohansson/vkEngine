#pragma once

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>
#include <algorithm>

#include "Window.h"
#include "Utils.h"

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities = {};
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Device
{
public:
	void destroy();

	void pickPhysicalDevice(VkInstance& instance, const VkSurfaceKHR& surface);
	void createLogicalDevice(const std::vector<const char*>& validationLayers, const VkSurfaceKHR& surface);
	void createSwapChain(Window window);
	void createImageViews();

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface) const;

	VkPhysicalDevice getPhysicalDevice() const;
	VkDevice getDevice() const;
	VkExtent2D getSwapChainExtent() const;
	VkFormat getSwapChainImageFormat() const;
	std::vector<VkImageView> getSwapChainImageViews() const;
	VkSwapchainKHR getSwapChain() const;
	VkQueue getGraphicsQueue() const;
	VkQueue getPresentQueue() const;

private:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, Window window);
};

