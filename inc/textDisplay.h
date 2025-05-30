#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <map>

struct Character {
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class TextDisplay {
public:
    TextDisplay();
    ~TextDisplay();
    void renderText(const std::string& text, float x, float y, float scale, glm::vec3 color);

private:
    std::map<char, Character> Characters;
    unsigned int VAO, VBO;
    unsigned int textShaderProgram;
    void initFreeType();
};