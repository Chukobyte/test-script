#pragma once

#include <string>

struct FilePosition {
    int index = -1;
    int line = 0;
    int col = -1;
    std::string fileName;
    std::string fileText;

    void Advance(char currentChar = '\0') {
        index++;
        col++;
        if (currentChar == '\n') {
            line++;
            col = 0;
        }
    }

    FilePosition Copy() {
        return { index, line, col, fileName, fileText };
    }
};
