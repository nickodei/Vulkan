cmake_minimum_required(VERSION 3.5.0)

project(Application)

find_package(Vulkan REQUIRED)

add_library(Application SHARED STATIC 
    bootstrap.hpp
    bootstrap.cpp
    application.hpp
    application.cpp
    game_application.hpp
    game_application.cpp
)

target_link_libraries(Application PRIVATE
       Graphics
       glfw
       vk-bootstrap
       Vulkan::Headers
)
