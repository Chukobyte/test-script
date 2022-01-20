#include "token.h"

namespace TokenUtils {
std::string GetTypeString(TokenType type) {
    std::string typeString;
    if (type == TokenType::PLUS) {
        return "PLUS";
    } else if (type == TokenType::MINUS) {
        return "MINUS";
    } else if (type == TokenType::MULTIPLY) {
        return "MULTIPLY";
    } else if (type == TokenType::DIVIDE) {
        return "DIVIDE";
    } else if (type == TokenType::LEFT_PARENTHESE) {
        return "LEFT_PARENTHESE";
    } else if (type == TokenType::RIGHT_PARENTHESE) {
        return "RIGHT_PARENTHESE";
    } else if (type == TokenType::INT) {
        return "INT";
    } else if (type == TokenType::FLOAT) {
        return "FLOAT";
    } else if (type == TokenType::END_OF_FILE) {
        return "EOF";
    }
    return "NULL";
}

std::string GetTokenString(Token token) {
    if (!token.value.empty()) {
        return "{" + GetTypeString(token.type) + ":" + token.value + "}";
    } else {
        return GetTypeString(token.type);
    }
}

std::string GetAllTokensString(const std::vector<Token>& tokens) {
    std::string resultString;
    for (Token token : tokens) {
        resultString += TokenUtils::GetTokenString(token) + "\n";
    }
    if (!resultString.empty()) {
        resultString.resize(resultString.length() - 1);
    }
    return resultString;
}
}
