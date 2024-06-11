#pragma once

#include <stdexcept>
#include <syntax_tree/node.hpp>
namespace paracl {
namespace ast {

class InterpretVisitor final : public NodeVisitor {
private:
  std::vector<double> st;

public:
  void visit(const BinaryOperator *node) override {

    double operand1 = st.back();
    st.pop_back();
    double operand2 = st.back();
    st.pop_back();

    switch (node->op) {
    case BinaryOperatorEnum::PLUS:
      st.push_back(operand1 + operand2);
      break;
    case BinaryOperatorEnum::MINUS:
      st.push_back(operand2 - operand1);
      break;
    case BinaryOperatorEnum::MUL:
      st.push_back(operand1 * operand2);
      break;
    case BinaryOperatorEnum::DIV:
      if (operand1 == 0)
        throw std::logic_error("Division by zero encountered, failing...\n");
      st.push_back(operand2 / operand1);
      break;
    default:
      throw std::logic_error("Unknown Binary operator type in Dump Visitor");
      break;
    }
  }

  void visit(const UnaryOperator *node) override {
    double val = st.back();
    switch (node->op) {
    case UnaryOperatorEnum::MINUS:
      st.pop_back();
      st.push_back(-val);
      break;
    default:
      throw std::logic_error("Unknown Unary operator type in Dump Visitor");
      break;
    }
  }

  void visit(const Number *node) override { st.push_back(node->value); }

  double get_result() { return st.back(); }
};

} // namespace ast
} // namespace paracl
