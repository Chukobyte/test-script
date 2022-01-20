#pragma once

#include <string>

struct File {
    std::string name;
    std::string text;
};

class FileLoader {
  private:
    static std::string LoadFileText(const std::string& filePath);
  public:
    static File LoadFile(const std::string& filePath);
};
