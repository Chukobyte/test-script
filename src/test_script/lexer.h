#pragma once

#include <string>
#include <vector>

#include "token.h"

class Lexer {
  public:
    std::string text;
    std::string fileName;
    FilePosition position = {};
    char currentChar = '\0';

    Lexer(const std::string& fileName, const std::string& text);
    void Advance();
    TokenResult MakeTokens();
    Token MakeNumber();
};

class LexerUtils {
  public:
    static std::string GetTokenResultString(const TokenResult& tokenResult);
};
