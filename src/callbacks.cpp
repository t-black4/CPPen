#include "callbacks.h"
#include "textDisplay.h"
#include "textInput.h"
#include "fileOperater.h"   
#include <iostream>
#include <thread>
#include <chrono>


extern double scrollX;
extern double scrollY;

void Callbacks::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if (key == GLFW_KEY_S && (mods & GLFW_MOD_CONTROL)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        FileOperater::getInstance().setSaveFlag(true);
    }else {
        TextInput::getInstance().key_callback(key, scancode, action, mods);
    }
    
}

void Callbacks::glfw_character_callback(GLFWwindow* window, unsigned int codepoint) {
    TextInput::getInstance().character_callback(codepoint);
}

void Callbacks::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "Scroll: " << xoffset << ", " << yoffset << std::endl;
    // scrollX += xoffset;
    scrollY += yoffset * 10;
    scrollY = std::min(scrollY, 0.0);
}