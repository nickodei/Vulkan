#pragma once

#include <vulkan/vulkan_core.h>
#include <VkBootstrap.h>

namespace Engine {

struct ImGuiServiceConfiguration {
    void* window_handle;
    VkDevice device;
    VkInstance instance;
    VkPhysicalDevice gpu;
    VkQueue graphics_queue;
    VkRenderPass render_pass;
    vkb::Swapchain swapchain;
};

struct ImGuiService {
    void init(ImGuiServiceConfiguration& configuration);
    void shutdown();

    void new_frame();
};

} // namespace Engine
