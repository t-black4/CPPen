#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
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
    std::string getInputText() const { return std::string(inputText->begin(), inputText->end()); }
    // Delete copy constructor and assignment operator
    TextInput(const TextInput&) = delete;
    TextInput& operator=(const TextInput&) = delete;
    void setInputText(const std::string& text) { inputText->assign(text.begin(), text.end()); }
private:
    TextInput(); // Private constructor
    ~TextInput(); // Private destructor
    
    std::vector<char>* inputText;
    static TextInput* s_instance;
};
