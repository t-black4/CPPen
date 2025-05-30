cmake_minimum_required(VERSION 3.16)
project(cppen)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_OBJECT_PATH_MAX 250)

# Add GLAD library
add_library(glad
    external/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    external/glad/include
)

# Add include directories for the project
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW installed system-wide
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Find FreeType
find_package(Freetype REQUIRED)

include_directories(
    ${GLFW_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/inc
)

add_executable(cppen 
    src/main.cpp
    src/textDisplay.cpp
    src/textInput.cpp
    src/fileOperater.cpp
    src/callbacks.cpp
)

target_link_libraries(cppen
    glad
    ${GLFW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${FREETYPE_LIBRARIES}
)
