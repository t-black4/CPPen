cmake_minimum_required(VERSION 3.16)
project(OpenGLWindow)

# Generate compile_commands.json for better IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

# Add GLAD library
add_library(glad
    external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW installed system-wide
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(
    ${GLFW_INCLUDE_DIRS}
)

add_executable(OpenGLWindow main.cpp)

target_link_libraries(OpenGLWindow
    glad
    ${GLFW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
)
