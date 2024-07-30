#pragma once

#include <cstdint>
#include <string>

namespace Engine {

struct ApplicationConfiguration {
    uint32_t width;
    uint32_t height;
    std::string name;
    std::string shader_path;

    ApplicationConfiguration& w(uint32_t value) {
        width = value;
        return *this;
    }
    ApplicationConfiguration& h(uint32_t value) {
        height = value;
        return *this;
    }
    ApplicationConfiguration& name_(std::string value) {
        name = value;
        return *this;
    }
};

struct Application {
    virtual void create(const ApplicationConfiguration& applicationConfiguration){};
    virtual void destroy(){};
    virtual void mainLoop(){};
    void run(const ApplicationConfiguration& configuration);
};

} // namespace Engine
