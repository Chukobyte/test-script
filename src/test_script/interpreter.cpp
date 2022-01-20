#include "interpreter.h"

#include "node.h"
#include "runtime.h"

RunTimeResult Interpreter::Visit(Node* node, Context* context) {
    switch (node->type) {
    case NodeType::NUMBER: {
        return VisitNumberNode(node, context);
    }
    case NodeType::BINARY_OPERATOR: {
        return VisitBinaryOperatorNode(node, context);
    }
    case NodeType::UNARY_OPERATOR: {
        return VisitUnaryOperatorNode(node, context);
    }
    default: {
        return {};
    }
    }
}

RunTimeResult Interpreter::VisitNumberNode(Node* node, Context* context) {
    return RunTimeResult().Success(ValueNumber(node->token, node->start, node->end, context));
}

RunTimeResult Interpreter::VisitBinaryOperatorNode(Node* node, Context* context) {
    RunTimeResult runTimeResult = {};

    RunTimeResult leftNumber = runTimeResult.Register(Visit(node->leftFactor, context));
    if (leftNumber.error.type != ErrorType::NONE) {
        return leftNumber;
    }

    RunTimeResult rightNumber = runTimeResult.Register(Visit(node->rightFactor, context));
    if (rightNumber.error.type != ErrorType::NONE) {
        return rightNumber;
    }

    RunTimeResult result = {};
    if (node->token.type == TokenType::PLUS) {
        result = result.Register(leftNumber.value.AddedTo(rightNumber.value));
    } else if (node->token.type == TokenType::MINUS) {
        result = result.Register(leftNumber.value.SubbedBy(rightNumber.value));
    } else if (node->token.type == TokenType::MULTIPLY) {
        result = result.Register(leftNumber.value.MultipliedBy(rightNumber.value));
    } else if (node->token.type == TokenType::DIVIDE) {
        result = result.Register(leftNumber.value.DividedBy(rightNumber.value));
    } else if (node->token.type == TokenType::POWER) {
        result = result.Register(leftNumber.value.PoweredBy(rightNumber.value));
    }

    if (result.error.type != ErrorType::NONE) {
        return result;
    }

    result.value.start = node->start;
    result.value.end = node->end;
    return result;
}

RunTimeResult Interpreter::VisitUnaryOperatorNode(Node* node, Context* context) {
    RunTimeResult runTimeResult = {};
    RunTimeResult number = runTimeResult.Register(Visit(node->leftFactor, context));
    if (number.error.type != ErrorType::NONE) {
        return number;
    }

    if (node->token.type == TokenType::MINUS) {
        number = runTimeResult.Success(number.value.MultipliedBy(ValueNumber(-1)));
    }

    if (number.error.type != ErrorType::NONE) {
        return number;
    }

    number.value.start = node->start;
    number.value.end = node->end;
    return number;
}
