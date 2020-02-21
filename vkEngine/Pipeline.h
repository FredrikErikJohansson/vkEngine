#pragma once

#include <vulkan/vulkan.h>

#include <fstream>
#include <vector>

class Pipeline
{
public:
	void destroy(const VkDevice& device);
	void createGraphicsPipeline(const VkDevice& device, const VkExtent2D& swapChainExtent);

private:
	VkPipelineLayout pipelineLayout;

	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code, VkDevice device);
};

