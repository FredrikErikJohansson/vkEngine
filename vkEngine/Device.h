#pragma once

#include <vulkan/vulkan.h>

#include <stdexcept>
#include <vector>
#include <optional>
#include <set>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class Device
{
public:
	void destroy();

	void pickPhysicalDevice(VkInstance& instance, const VkSurfaceKHR& surface);
	void createLogicalDevice(const std::vector<const char*>& validationLayers, const VkSurfaceKHR& surface);

private:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = {};
	VkQueue graphicsQueue = {};
	VkQueue presentQueue = {};

	bool isDeviceSuitable(VkPhysicalDevice device, VkSurfaceKHR surface);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);
};

