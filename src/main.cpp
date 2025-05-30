// Standard C++ headers
#include <iostream>
#include <string>

#include "fileOperater.h"
#include "textDisplay.h"
#include "textInput.h"
#include "callbacks.h"
// OpenGL headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Use standard namespace
using namespace std;

int windowWidth = 1200;
int windowHeight = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, windowWidth, windowHeight);
}

int main(int argc, char* argv[]) {
    // Initialize GLFW
    FileOperater::getInstance().setFilename("output.txt");
    FileOperater::getInstance().readFile();
    TextInput::getInstance().setInputText(FileOperater::getInstance().returnContent());
    
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // OpenGL version 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "CPPen", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwSetCharCallback(window, Callbacks::glfw_character_callback);
    glfwSetKeyCallback(window, Callbacks::glfw_key_callback);

    glfwMakeContextCurrent(window);

    // Load OpenGL functions via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    TextDisplay textDisplay;

    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textDisplay.setTextWidth(24);
    textDisplay.setTextHeight(24);
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render the input text
        FileOperater::getInstance().setContent(TextInput::getInstance().getInputText()); // Update the content
        textDisplay.renderText(FileOperater::getInstance().returnContent(), 0, windowHeight - textDisplay.getTextHeight(), 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    textDisplay.cleanup();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

