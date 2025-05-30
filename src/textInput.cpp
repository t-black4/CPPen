#include "textInput.h"
#include <iostream>

#include "fileSave.h"
TextInput* TextInput::s_instance = nullptr;

TextInput& TextInput::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new TextInput();
    }
    return *s_instance;
}

TextInput::TextInput() : inputText(new std::vector<char>()) {}

TextInput::~TextInput() {
    if (s_instance) {
        delete s_instance;
        s_instance = nullptr;
    }
}

void TextInput::character_callback(unsigned int codepoint) {
    // Regular character input (printable ASCII range)
    if (codepoint >= 32 && codepoint <= 126) {
        inputText->push_back(static_cast<char>(codepoint));
    }
}

void TextInput::key_callback(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_BACKSPACE) {
            if (!inputText->empty()) {
                inputText->pop_back();
            }
        } else if (key == GLFW_KEY_ENTER) {
            inputText->push_back('\n');
        }
    }
}
