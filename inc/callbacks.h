#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Callbacks {
public:
    static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void glfw_character_callback(GLFWwindow* window, unsigned int codepoint);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};