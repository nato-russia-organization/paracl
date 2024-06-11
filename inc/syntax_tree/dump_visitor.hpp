#pragma once

#include <iostream>
#include <stdexcept>
#include <syntax_tree/node.hpp>
namespace paracl {
namespace ast {

class DumpVisitor final : public NodeVisitor {

public:
  void visit(const BinaryOperator *node) override {
    switch (node->op) {
    case BinaryOperatorEnum::PLUS:
      std::cout << " + ";
      break;
    case BinaryOperatorEnum::MINUS:
      std::cout << " - ";
      break;
    case BinaryOperatorEnum::MUL:
      std::cout << " * ";
      break;
    case BinaryOperatorEnum::DIV:
      std::cout << " / ";
      break;
    default:
      throw std::logic_error("Unknown Binary operator type in Dump Visitor");
    }
  }

  void visit(const UnaryOperator *node) override {
    switch (node->op) {
    case UnaryOperatorEnum::MINUS:
      std::cout << " - ";
      break;
    default:
      throw std::logic_error("Unknown Unary operator type in Dump Visitor");
    }
  }

  void visit(const Number *node) override { std::cout << node->value << " "; }
};

} // namespace ast
} // namespace paracl
