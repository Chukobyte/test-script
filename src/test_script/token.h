#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "error.h"

enum class TokenType {
    _NULL,
    INT,
    FLOAT,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LEFT_PARENTHESE,
    RIGHT_PARENTHESE,
    POWER,
    END_OF_FILE
};

struct Token {
    TokenType type = TokenType::_NULL;
    std::string value;
    FilePosition start = {};
    FilePosition end = {};

    Token(TokenType type = TokenType::_NULL, std::string value = "", FilePosition startPos = {}, FilePosition endPos = {}) : type(type), value(std::move(value)) {
        if (start.index > -1) {
            start = startPos.Copy();
            end = startPos.Copy();
            end.Advance();
        }
        if (endPos.index > -1) {
            end = endPos.Copy();
        }
    }
};

struct TokenResult {
    std::vector<Token> tokens = {};
    Error error = {};
};

namespace TokenUtils {
std::string GetTypeString(TokenType type);
std::string GetTokenString(Token token);
std::string GetAllTokensString(const std::vector<Token>& tokens);
};
