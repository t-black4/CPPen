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

class FileOperater {
private:
    FileOperater(); // Private constructor for singleton

    ~FileOperater(); // Private destructor

    FileOperater(const FileOperater&) = delete;  // Delete copy constructor
    FileOperater& operator=(const FileOperater&) = delete;  // Delete assignment operator
    FileOperater(const std::string& filename);
    bool saveflag;

    static FileOperater* s_instance;

public:
    void setFilename(const std::string& filename) { this->filename = filename; }
    std::string returnContent() const { return content; }
    void setContent(const std::string& content) { this->content = content; }
    static FileOperater& getInstance();
    std::string content;
    std::string filename;
    void readFile();
    void saveFile();
    void setSaveFlag(bool flag) { saveflag = flag; }
    bool getSaveFlag() const { return saveflag; }
};
