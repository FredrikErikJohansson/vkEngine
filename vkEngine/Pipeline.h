#pragma once

#include <vulkan/vulkan.h>

#include <fstream>
#include <vector>

#include "Utils.h"
#include "Device.h"

class Pipeline
{
public:
	void destroy(const VkDevice& device);
	void createRenderPass(const VkDevice& device, const VkFormat& swapChainExtent);
	void createGraphicsPipeline(const VkDevice& device, const VkExtent2D& swapChainExtent);
	void createFramebuffers(const VkDevice& device, const VkExtent2D& swapChainExtent, const std::vector<VkImageView>& swapChainImageViews);
	void createCommandPool(const Device& device, const VkSurfaceKHR& surface);
	void createCommandBuffers(const VkDevice& device, const VkExtent2D& swapChainExtent);
	void createSemaphores(const VkDevice& device);

	void drawFrame(const VkDevice& device, const VkQueue& graphicsQueue, const VkQueue& presentQueue, const VkSwapchainKHR& swapChain);

private:
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;

	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
};

