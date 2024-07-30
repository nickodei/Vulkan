#include "application.hpp"

namespace Engine {

void Application::run(const ApplicationConfiguration& configuration) {
    create(configuration);
    mainLoop();
    destroy();
}

} // namespace Engine
