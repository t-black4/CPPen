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

// Represents a single character glyph with its OpenGL texture and metrics
struct Character {
    unsigned int TextureID;  // OpenGL texture ID for the character's bitmap
    glm::ivec2 Size;        // Size of the glyph in pixels (width, height)
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Horizontal offset to advance to next glyph
};

class TextDisplay {
public:
    TextDisplay();
    ~TextDisplay();
    void renderText(const std::string& text, float x, float y);
    void cleanup();
    void setTextWidth(int width) { textWidth = width; }
    void setTextHeight(int height) { textHeight = height; }
    void setWindowWidth(int width) { windowWidth = width; }
    void setWindowHeight(int height) { windowHeight = height; }
    int getTextWidth() const { return textWidth; }
    int getTextHeight() const { return textHeight; }
    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }
    bool isTextChanged() const { return textChanged; }
    void setTextChanged(bool changed) { textChanged = changed; }
private:
    int windowWidth = 1200;
    int windowHeight = 800;
    int textWidth = 12;
    int textHeight = 12;
    std::map<char, Character> Characters;
    unsigned int VAO = 0, VBO = 0;
    unsigned int textShaderProgram = 0;
    void initFreeType();
    bool textChanged = false;
};