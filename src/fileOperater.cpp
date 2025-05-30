
#include "fileOperater.h"
#include <fstream>
#include <iostream>

FileOperater* FileOperater::s_instance = nullptr;

FileOperater& FileOperater::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new FileOperater();
    }
    return *s_instance;
}

FileOperater::FileOperater() {
    
}

FileOperater::~FileOperater() {
    
}

FileOperater::FileOperater(const std::string& filename) {
    setFilename(filename);
    readFile();
}

void FileOperater::readFile() {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
        content = "";
    }
}


void FileOperater::saveFile() {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << content;
        std::cout << "File saved successfully: " << filename << std::endl;
        file << std::flush;
        file.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}
