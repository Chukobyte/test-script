#include "file_loader.h"

#include <fstream>
#include <sstream>

std::string FileLoader::LoadFileText(const std::string& filePath) {
    std::ifstream file(filePath);
    std::stringstream fileBuffer;
    fileBuffer << file.rdbuf();
    return fileBuffer.str();
}

File FileLoader::LoadFile(const std::string& filePath) {
    return { filePath, LoadFileText(filePath) };
}
