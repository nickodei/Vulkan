cmake_minimum_required(VERSION 3.5.0)

project(app)

add_subdirectory(graphics)
add_subdirectory(application)

add_executable(app main.cpp)
target_link_libraries(app Application)

target_include_directories(app PRIVATE ${CMAKE_CURRENT_BINARY_DIR}) # path to build directory for shaders

add_custom_command(
    TARGET app
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/shaders ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR})

configure_file (
    "${PROJECT_SOURCE_DIR}/config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/config.hpp"
)
