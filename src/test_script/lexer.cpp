#include "lexer.h"

#include "token.h"

Lexer::Lexer(const std::string& fileName, const std::string& text) :
    fileName(fileName),
    text(text),
    position({ -1, 0, -1, fileName, text }) {
    Advance();
}

void Lexer::Advance() {
    position.Advance(currentChar);
    if (position.index <= text.length()) {
        currentChar = text[position.index];
    }
}

TokenResult Lexer::MakeTokens() {
    std::vector<Token> tokens = {};
    while (currentChar != '\0') {
        if (currentChar == '\t' || currentChar == ' ' || currentChar == '\n') {
            Advance();
        } else if (currentChar == '+') {
            tokens.emplace_back(Token{TokenType::PLUS, "", position});
            Advance();
        } else if (currentChar == '-') {
            tokens.emplace_back(Token{TokenType::MINUS, "", position});
            Advance();
        } else if (currentChar == '*') {
            tokens.emplace_back(Token{TokenType::MULTIPLY, "", position});
            Advance();
        } else if (currentChar == '/') {
            tokens.emplace_back(Token{TokenType::DIVIDE, "", position});
            Advance();
        } else if (currentChar == '(') {
            tokens.emplace_back(Token{TokenType::LEFT_PARENTHESE, "", position});
            Advance();
        } else if (currentChar == ')') {
            tokens.emplace_back(Token{TokenType::RIGHT_PARENTHESE, "", position});
            Advance();
        } else if (currentChar == '^') {
            tokens.emplace_back(Token{TokenType::POWER, "", position});
            Advance();
        } else if (isdigit(currentChar)) {
            tokens.emplace_back(MakeNumber());
        } else {
            FilePosition startPosition = position.Copy();
            position.Advance(currentChar);
            return TokenResult{
                {},
                Error{
                    ErrorType::ILLEGAL_CHARACTER,
                    "Illegal character '" + std::string(1, currentChar) + "'",
                    startPosition,
                    {}
                }
            };
        }
    }
    tokens.emplace_back(Token{ TokenType::END_OF_FILE, "", position });
    return TokenResult{ tokens };
}

Token Lexer::MakeNumber() {
    std::string numText;
    int dotCount = 0;
    FilePosition positionStart = position.Copy();

    while (isdigit(currentChar) || currentChar == '.') {
        if (currentChar == '.') {
            if (dotCount == 1) {
                break;
            }
            dotCount++;
            numText += ".";
        } else {
            numText += currentChar;
        }
        Advance();
    }
    if (dotCount == 0) {
        return Token{ TokenType::INT, numText, positionStart, position };
    } else {
        return Token{ TokenType::FLOAT, numText, positionStart, position };
    }
}

std::string LexerUtils::GetTokenResultString(const TokenResult& tokenResult) {
    std::string resultString;
    if (!tokenResult.tokens.empty()) {
        resultString = TokenUtils::GetAllTokensString(tokenResult.tokens);
    } else {
        resultString = ErrorUtils::GetErrorString(tokenResult.error);
    }
    return resultString;
}
