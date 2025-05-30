// Standard C++ headers
#include <iostream>
#include <string>

#include "textDisplay.h"
#include "textInput.h"
// OpenGL headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Use standard namespace
using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Initialize GLFW
    
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // OpenGL version 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "CPPen", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetCharCallback(window, TextInput::glfw_character_callback);

    glfwMakeContextCurrent(window);

    // Load OpenGL functions via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    TextDisplay textDisplay;

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the input text
        textDisplay.renderText(TextInput::getInstance().getInputText(), 25.0f, 300.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

