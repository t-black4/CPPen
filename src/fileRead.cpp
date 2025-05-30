
#include "fileRead.h"
#include <fstream>
#include <iostream>


FileRead::FileRead(const std::string& filename) {
    readFile(filename);
}

void FileRead::readFile(const std::string& filename) {
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
