#pragma once

#include "application.hpp"

namespace Engine {

struct ImGuiService;

struct GameApplication : public Application {
    void create(const Engine::ApplicationConfiguration& configuration) override;
    void mainLoop() override;

    // Init init;
    // RenderData render_data;
};

} // namespace Engine
