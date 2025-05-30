#include "textInput.h"

TextInput* TextInput::s_instance = nullptr;

TextInput& TextInput::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new TextInput();
    }
    return *s_instance;
}

TextInput::TextInput() : inputText("") {}

TextInput::~TextInput() {
    if (s_instance) {
        delete s_instance;
        s_instance = nullptr;
    }
}

void TextInput::character_callback(GLFWwindow* window, unsigned int codepoint) {
    if (codepoint == 8) {
        if (!inputText.empty()) {
            inputText.pop_back();
        }
    } else if (codepoint == 13) {
        inputText += "\n";
    } else {
        inputText += static_cast<char>(codepoint);
    }
}

void TextInput::glfw_character_callback(GLFWwindow* window, unsigned int codepoint) {
    TextInput::getInstance().character_callback(window, codepoint);
}