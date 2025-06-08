#include <glad/glad.h>
#include <GLFW/glfw3.h>
    /**
     * TextInput is a Singleton class that keeps track of the user's input from the keyboard.
     * The class provides an interface for GLFW to callback the character_callback function when a key is pressed.
     * The class also provides a method to get the current input text.
     */
class TextInput {
public: 
    static TextInput& getInstance();
    void character_callback(unsigned int codepoint);
    void key_callback(int key, int scancode, int action, int mods);
    char getInputChar() const { return m_currentChar; }
    bool isNewChar() const { return newchar; }
    void setNewChar(bool newchar) { this->newchar = newchar; }
    // Delete copy constructor and assignment operator
    TextInput(const TextInput&) = delete;
    TextInput& operator=(const TextInput&) = delete;
    void setInputChar(char ch) { m_currentChar = ch; }
private:
    TextInput(); // Private constructor
    ~TextInput(); // Private destructor
    bool newchar;
    char m_currentChar;
    static TextInput* s_instance;
};
