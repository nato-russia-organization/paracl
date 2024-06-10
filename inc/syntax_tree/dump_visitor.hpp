#pragma once

#include <iostream>
#include <syntax_tree/node.hpp>
namespace paracl {
namespace ast {

class DumpVisitor final : public NodeVisitor {

public:
  void visit(const BinaryOperator *node) const override {
    std::cout << " bin op \n";
  }
  void visit(const UnaryOperator *node) const override {
    std::cout << " un op \n";
  }

  void visit(const Integer *node) const override {
    std::cout << node->value << "\n";
  }

  void visit(const Float *node) const override {
    std::cout << node->value << "\n";
  }

  void visit(const Double *node) const override {
    std::cout << node->value << "\n";
  }
};

} // namespace ast
} // namespace paracl
