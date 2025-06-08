#include "textDisplay.h"
#include <iostream>

// Vertex shader for text rendering
// This shader processes each vertex of our text quads
const char* vertexShaderSource = R"(
    #version 330 core
    // Each vertex has 4 components: xy for position, zw for texture coordinates
    layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
    // Pass texture coordinates to fragment shader
    out vec2 TexCoords;
    // Projection matrix for proper 2D positioning in screen space
    uniform mat4 projection;

    void main() {
        // Transform vertex position using projection matrix
        gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
        // Forward texture coordinates to fragment shader
        TexCoords = vertex.zw;
    }
)";

// Fragment shader for text rendering
// This shader handles the actual coloring of each pixel in the text
const char* fragmentShaderSource = R"(
    #version 330 core
    // Texture coordinates from vertex shader
    in vec2 TexCoords;
    // Final output color
    out vec4 color;
    // Glyph texture sampler
    uniform sampler2D text;
    void main() {
        // Sample the texture (r channel contains glyph data)
        // and use it as alpha channel with white color
        color = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    }
)";

TextDisplay::TextDisplay() {
    initFreeType();
}

TextDisplay::~TextDisplay() {
}

void TextDisplay::cleanup() {
    for (auto& ch : Characters) {
        if (ch.second.TextureID)
            glDeleteTextures(1, &ch.second.TextureID);
    }
    Characters.clear();
    if (VAO)
        glDeleteVertexArrays(1, &VAO);
    if (VBO)
        glDeleteBuffers(1, &VBO);
    if (textShaderProgram)
        glDeleteProgram(textShaderProgram);
}

void TextDisplay::initFreeType() {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, textHeight);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create and compile shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    textShaderProgram = glCreateProgram();
    glAttachShader(textShaderProgram, vertexShader);
    glAttachShader(textShaderProgram, fragmentShader);
    glLinkProgram(textShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void TextDisplay::renderText(const std::string& text, float x, float y) {
    glUseProgram(textShaderProgram);
    // Use actual window dimensions and flip Y coordinates for top-left origin
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight));
    glUniformMatrix4fv(glGetUniformLocation(textShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(textShaderProgram, "textColor"), 1.0f, 1.0f, 1.0f);
    // Store the initial X position for resetting on newlines
    float startX = x;

    // Convert y coordinate from top-left (where y_param is scrollY) to OpenGL's bottom-left origin.
    // current_y will represent the baseline of the *first* line of text.
    float current_y = windowHeight - y - textHeight; // Subtract textHeight to set baseline for the first line

    // Clamp current_y if it goes too far down (optional, based on desired behavior)
    // if (current_y < 0) current_y = 0; 

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (char c : text) {   
        if (c == '\n') {
            x = 0;
            y -= textHeight / 1.9; // Moving down means increasing Y in OpenGL coordinates
            continue;
        }

        Character ch = Characters[c];

        float xpos = x + ch.Bearing.x * 1;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * 1;

        float w = ch.Size.x * 1;
        float h = ch.Size.y * 1;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * 1;
    }

    Character ch = Characters['_'];

    float xpos = x + ch.Bearing.x * 1;
    float ypos = y - (ch.Size.y - ch.Bearing.y) * 1;

    float w = ch.Size.x * 1;
    float h = ch.Size.y * 1;

    float vertices[6][4] = {
        { xpos,     ypos + h,   0.0f, 0.0f },
        { xpos,     ypos,       0.0f, 1.0f },
        { xpos + w, ypos,       1.0f, 1.0f },

        { xpos,     ypos + h,   0.0f, 0.0f },
        { xpos + w, ypos,       1.0f, 1.0f },
        { xpos + w, ypos + h,   1.0f, 0.0f }
    };

    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    x += (ch.Advance >> 6) * 1;
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}