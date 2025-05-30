#include <string>
#include <GLFW/glfw3.h>

class TextInput {
public:
    static TextInput& getInstance();
    void character_callback(GLFWwindow* window, unsigned int codepoint);
    std::string getInputText() const { return inputText; }
    static void glfw_character_callback(GLFWwindow* window, unsigned int codepoint);

    // Delete copy constructor and assignment operator
    TextInput(const TextInput&) = delete;
    TextInput& operator=(const TextInput&) = delete;

private:
    TextInput(); // Private constructor
    ~TextInput(); // Private destructor
    
    std::string inputText;
    static TextInput* s_instance;
};
