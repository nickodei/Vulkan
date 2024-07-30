cmake_minimum_required(VERSION 3.5.0)

project(Graphics)
find_package(Vulkan REQUIRED)

add_library(Graphics SHARED STATIC 
    imgui.cpp
    imgui.hpp
)

target_link_libraries(Graphics PUBLIC
       glfw
       Vulkan::Vulkan
       imgui
)
