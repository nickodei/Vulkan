#include "application/game_application.hpp"
#include "config.hpp"

int main() {
    Engine::ApplicationConfiguration configuration;
    configuration.shader_path = std::string(EXAMPLE_BUILD_DIRECTORY);

    Engine::GameApplication application;
    application.run(configuration);
}
