#pragma once

#include "token.h"

enum class NodeType {
    INVALID,
    NUMBER,
    BINARY_OPERATOR,
    UNARY_OPERATOR
};

struct NodeData {
    int intValue;
    float floatValue;
};

struct Node {
    NodeType type = NodeType::INVALID;
    Token token {};
    Node* leftFactor = nullptr;
    Node* rightFactor = nullptr;
    FilePosition start = {};
    FilePosition end = {};
};

namespace NodeUtils {
std::string GetNodeString(Node* node);
}
