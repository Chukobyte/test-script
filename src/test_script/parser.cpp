#include "parser.h"

#include <sstream>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
    Advance();
}

Token Parser::Advance() {
    tokenIndex++;
    if (tokenIndex < tokens.size()) {
        currentToken = tokens[tokenIndex];
    }
    return currentToken;
}

ParseResult Parser::Factor() {
    ParseResult parseResult = {};
    Token factorCurrentToken = currentToken;
    switch (currentToken.type) {
    case TokenType::PLUS:
    case TokenType::MINUS: {
        Advance();
        ParseResult factor = parseResult.Register(Factor());
        if (factor.error.type != ErrorType::NONE) {
            return factor;
        }
        Node* unaryNode = CreateNode(
                              NodeType::UNARY_OPERATOR,
                              factorCurrentToken,
                              factor.node,
                              nullptr,
                              factorCurrentToken.start,
                              factor.node->end
                          );
        return parseResult.Success(unaryNode);
    }
    default: {
        return Power();
    }
    }
}

ParseResult Parser::Atom() {
    ParseResult parseResult = {};
    Token factorCurrentToken = currentToken;
    switch (currentToken.type) {
    case TokenType::INT: {
        Advance();
        Node* intNumberNode = CreateNode(
                                  NodeType::NUMBER,
                                  factorCurrentToken,
                                  nullptr,
                                  nullptr,
                                  factorCurrentToken.start,
                                  factorCurrentToken.end
                              );
        return parseResult.Success(intNumberNode);
    }
    case TokenType::FLOAT: {
        Advance();
        Node* floatNumberNode = CreateNode(
                                    NodeType::NUMBER,
                                    factorCurrentToken,
                                    nullptr,
                                    nullptr,
                                    factorCurrentToken.start,
                                    factorCurrentToken.end
                                );
        return parseResult.Success(floatNumberNode);
    }
    case TokenType::LEFT_PARENTHESE: {
        Advance();
        ParseResult expression = parseResult.Register(Expression());
        if (expression.error.type != ErrorType::NONE) {
            return expression;
        }
        if (currentToken.type == TokenType::RIGHT_PARENTHESE) {
            Advance();
            return parseResult.Success(expression.node);
        } else {
            return parseResult.Failure(
            Error{
                ErrorType::INVALID_SYNTAX,
                "Expected ')'",
                currentToken.start,
                currentToken.end
            });
        }
    }
    default: {
        return parseResult.Failure(
        Error{
            ErrorType::INVALID_SYNTAX,
            "Expected int, float, '+', '-', or '('",
            factorCurrentToken.start,
            factorCurrentToken.end
        });
    }
    }
}

ParseResult Parser::Power() {
    auto atomFunc = [this]() {
        return Atom();
    };
    auto factorFunc = [this]() {
        return Factor();
    };
    return BinaryOperation(atomFunc, { TokenType::POWER }, factorFunc);
}

ParseResult Parser::Term() {
    auto factorFunc = [this]() {
        return Factor();
    };
    return BinaryOperation(factorFunc, { TokenType::MULTIPLY, TokenType::DIVIDE }, factorFunc);
}

ParseResult Parser::Expression() {
    auto termFunc = [this]() {
        return Term();
    };
    return BinaryOperation(termFunc, { TokenType::PLUS, TokenType::MINUS }, termFunc);
}

ParseResult Parser::BinaryOperation(const std::function<ParseResult()>& funcA, const std::vector<TokenType>& operators, const std::function<ParseResult()>& funcB) {
    ParseResult parseResult = {};
    ParseResult leftFactor = parseResult.Register(funcA());
    if (leftFactor.error.type != ErrorType::NONE) {
        return leftFactor;
    }

    while (IsTokenTypeInOperators(currentToken, operators)) {
        Token operatorToken = currentToken;
        Advance();
        ParseResult rightFactor = parseResult.Register(funcB());
        if (rightFactor.error.type != ErrorType::NONE) {
            return rightFactor;
        }
        Node* leftFactorNode = CreateNode(
                                   NodeType::BINARY_OPERATOR,
                                   operatorToken,
                                   leftFactor.node,
                                   rightFactor.node,
                                   leftFactor.node->start,
                                   rightFactor.node->end
                               );
        leftFactor = parseResult.Success(leftFactorNode);
    }
    return parseResult.Success(leftFactor.node);
}

ParseResult Parser::Parse() {
    ParseResult result = Expression();
    if (result.error.type != ErrorType::NONE && currentToken.type != TokenType::END_OF_FILE) {
        return result.Failure(Error{
            ErrorType::INVALID_SYNTAX,
            "Expected '+', '-', '*' or '/'",
            currentToken.start,
            currentToken.end
        });
    }
    return result;
}

Node* Parser::CreateNode(const NodeType& type, const Token& token, Node* leftFactor, Node* rightFactor, const FilePosition& start, const FilePosition& end) {
    Node* newNode = new Node{ type, token, leftFactor, rightFactor, start, end };
    nodeRegistry.emplace_back(newNode);
    return newNode;
}

void Parser::ClearNodeData() {
    for (Node* node : nodeRegistry) {
        delete node;
    }
    nodeRegistry.clear();
}
