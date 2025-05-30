#include "callbacks.h"
#include "textInput.h"
#include "fileSave.h"   


void Callbacks::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_S && (mods & GLFW_MOD_CONTROL)) {
        FileSave::getInstance().saveFile("output.txt", TextInput::getInstance().getInputText());
    }else {
        TextInput::getInstance().key_callback(key, scancode, action, mods);
    }
    
}

void Callbacks::glfw_character_callback(GLFWwindow* window, unsigned int codepoint) {
    TextInput::getInstance().character_callback(codepoint);
}
        