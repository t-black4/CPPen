#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef __cplusplus
}
#endif

#include <string>

class FileSave {
private:
    FileSave(); // Private constructor for singleton
    ~FileSave(); // Private destructor
    FileSave(const FileSave&) = delete;  // Delete copy constructor
    FileSave& operator=(const FileSave&) = delete;  // Delete assignment operator

    static FileSave* s_instance;

public:
    static FileSave& getInstance();
    void saveFile(const std::string& filename, const std::string& content);
};
