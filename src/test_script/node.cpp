#include "node.h"

//class NumberNode:
//	def __init__(self, tok):
//		self.tok = tok
//
//	def __repr__(self):
//		return f'{self.tok}'
//
//class BinOpNode:
//	def __init__(self, left_node, op_tok, right_node):
//		self.left_node = left_node
//		self.op_tok = op_tok
//		self.right_node = right_node
//
//	def __repr__(self):
//		return f'({self.left_node}, {self.op_tok}, {self.right_node})'
//
//class UnaryOpNode:
//	def __init__(self, op_tok, node):
//		self.op_tok = op_tok
//		self.node = node
//
//	def __repr__(self):
//		return f'({self.op_tok}, {self.node})'

namespace {
std::string GetNodeDataString(const NodeData& data) {
    return "";
}
}

namespace NodeUtils {
std::string GetNodeString(Node* node) {
    switch (node->type) {
    case NodeType::BINARY_OPERATOR:
        return "(" + GetNodeString(node->leftFactor) + ", " + TokenUtils::GetTokenString(node->token) + ", " +
               GetNodeString(node->rightFactor) + ")";
    case NodeType::UNARY_OPERATOR:
        return "(" + TokenUtils::GetTokenString(node->token) + ", " + GetNodeString(node->leftFactor) + ")";
    case NodeType::NUMBER:
        return TokenUtils::GetTokenString(node->token);
    case NodeType::INVALID:
    default:
        return "Invalid Node!";
    }
}
}