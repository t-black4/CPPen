#ifndef FILE_READ_H
#define FILE_READ_H

#include <string>

class FileRead {
public:
    FileRead(const std::string& filename);
    void readFile(const std::string& filename);
    std::string returnContent() const { return content; }
private:
    std::string content;
};

#endif // FILE_READ_H
