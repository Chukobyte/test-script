#pragma once

#include <vector>
#include <functional>

#include "node.h"

struct ParseResult {
    Error error = {};
    Node* node = nullptr;

    ParseResult Register(const ParseResult& parseResult) {
        if (parseResult.error.type != ErrorType::NONE) {
            error = parseResult.error;
        }
        node = parseResult.node;
        return ParseResult{ error, node };
    }

    ParseResult Success(Node* node) {
        node = node;
        return ParseResult{ error, node };
    }

    ParseResult Failure(Error error) {
        error = error;
        return ParseResult{ error, node };
    }
};

class Parser {
  private:
    std::vector<Token> tokens = {};
    Token currentToken = {};
    int tokenIndex = -1;
    std::vector<Node*> nodeRegistry = {};

    Token Advance();
    ParseResult Factor();
    ParseResult Atom();
    ParseResult Power();
    ParseResult Term();
    ParseResult Expression();
    ParseResult BinaryOperation(const std::function<ParseResult()>& funcA, const std::vector<TokenType>& operators, const std::function<ParseResult()>& funcB);
    Node* CreateNode(const NodeType& type = NodeType::INVALID, const Token& token = {}, Node* leftFactor = nullptr, Node* rightFactor = nullptr, const FilePosition& start = {}, const FilePosition& end = {});

    static bool IsTokenTypeInOperators(const Token& token, const std::vector<TokenType>& operators) {
        for (auto& op : operators) {
            if (token.type == op) {
                return true;
            }
        }
        return false;
    }

  public:
    Parser(std::vector<Token> tokens);
    ParseResult Parse();
    void ClearNodeData();
};

