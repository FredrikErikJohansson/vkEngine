#pragma once

#include <vulkan/vulkan.h>

#include <stdexcept>
#include <vector>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class Device
{
public:
	void destroy();

	void pickPhysicalDevice(VkInstance& instance);
	void createLogicalDevice(const std::vector<const char*>& validationLayers);

private:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device;
	VkQueue graphicsQueue;

	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};

