#include "game_application.hpp"
#include "../graphics/imgui.hpp"
#include "bootstrap.cpp"
#include "bootstrap.hpp"
#include <imgui.h>
#include <stdexcept>

namespace Engine {

// GameApplication ////////////////////////////////////////////////////////////////

Init init;
RenderData render_data;
Engine::ImGuiService imGuiService;

void GameApplication::create(const Engine::ApplicationConfiguration& configuration) {
    if (0 != device_initialization(init)) throw std::runtime_error("Devide initialization failed");
    if (0 != create_swapchain(init)) throw std::runtime_error("Swap creation failed");
    if (0 != get_queues(init, render_data)) throw std::runtime_error("Queue initialization failed");
    if (0 != create_render_pass(init, render_data)) throw std::runtime_error("Render pass creation failed");
    if (0 != create_graphics_pipeline(init, render_data, configuration.shader_path))
        throw std::runtime_error("Render pass creation failed");
    if (0 != create_framebuffers(init, render_data)) throw std::runtime_error("Render pass creation failed");
    if (0 != create_command_pool(init, render_data)) throw std::runtime_error("Render pass creation failed");
    if (0 != create_command_buffers(init, render_data)) throw std::runtime_error("Render pass creation failed");
    if (0 != create_sync_objects(init, render_data)) throw std::runtime_error("Render pass creation failed");

    Engine::ImGuiServiceConfiguration imGuiConfiguration;
    imGuiConfiguration.device = init.device.device;
    imGuiConfiguration.gpu = init.device.physical_device;
    imGuiConfiguration.instance = init.instance.instance;
    imGuiConfiguration.swapchain = init.swapchain;
    imGuiConfiguration.graphics_queue = render_data.graphics_queue;
    imGuiConfiguration.window_handle = init.window;
    imGuiConfiguration.render_pass = render_data.render_pass;

    imGuiService.init(imGuiConfiguration);
};

void GameApplication::mainLoop() {
    while (!glfwWindowShouldClose(init.window)) {
        glfwPollEvents();

        imGuiService.new_frame();

        int res = draw_frame(init, render_data);
        if (res != 0) {
            std::cout << "failed to draw frame \n";
            break;
        }
    }

    init.disp.deviceWaitIdle();
    cleanup(init, render_data);
};

} // namespace Engine
