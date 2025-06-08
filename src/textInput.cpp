#include "textInput.h"
#include <iostream>

TextInput* TextInput::s_instance = nullptr;

TextInput& TextInput::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new TextInput();
    }
    return *s_instance;
}

TextInput::TextInput() : m_currentChar('\0') {}

TextInput::~TextInput() {
    // m_currentChar does not require manual deallocation
}

void TextInput::character_callback(unsigned int codepoint) {
    // Regular character input (printable ASCII range)
    
    if (codepoint >= 32 && codepoint <= 126) {
        m_currentChar = static_cast<char>(codepoint);
        newchar = true;
    }
}

void TextInput::key_callback(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_BACKSPACE) {
            m_currentChar = '\0'; // Set to null character on backspace
            newchar = true;
        } else if (key == GLFW_KEY_ENTER) {
            m_currentChar = '\n'; // Set to newline on enter
            newchar = true;
        }
    }
}
