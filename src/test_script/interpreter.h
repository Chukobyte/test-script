#pragma once

class Node;
class RunTimeResult;
class Context;

class Interpreter {
  private:
    RunTimeResult VisitNumberNode(Node* node, Context* context);
    RunTimeResult VisitBinaryOperatorNode(Node* node, Context* context);
    RunTimeResult VisitUnaryOperatorNode(Node* node, Context* context);
  public:
    RunTimeResult Visit(Node* node, Context* context);
};
