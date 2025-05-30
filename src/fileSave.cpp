#include "fileSave.h"
#include <iostream>
#include <fstream>

FileSave* FileSave::s_instance = nullptr;

FileSave& FileSave::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new FileSave();
    }
    return *s_instance;
}

FileSave::FileSave() {
    
}

FileSave::~FileSave() {
    
}

void FileSave::saveFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (char c : content) {
            file << c;
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

