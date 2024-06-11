#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <syntax_tree/visitor.hpp>
#include <vector>

namespace paracl {
namespace ast {

enum class BinaryOperatorEnum { PLUS, MINUS, MUL, DIV };
enum class UnaryOperatorEnum { MINUS };

struct Node {

  void add_child(Node *child) {
    if (_is_leaf) {
      _is_leaf = false;
      child->_is_last = true;
    } else {
      child->set_idx(children.back()->get_idx() + 1);
      children.back()->_is_last = false;
    }

    child->set_parent(this);
    child->set_depth(depth + 1);
    children.push_back(child);
  }

  [[nodiscard]] const std::vector<Node *> get_children() const {
    return children;
  }
  [[nodiscard]] const Node *get_parent() const { return parent; }
  [[nodiscard]] size_t get_idx() const { return idx; }
  [[nodiscard]] size_t get_depth() const { return depth; }

  [[nodiscard]] const bool is_last() const { return _is_last; }
  [[nodiscard]] const bool is_leaf() const { return _is_leaf; }

  void set_parent(Node *parent_node) { parent = parent_node; }
  void set_idx(size_t _idx) { idx = _idx; }
  void set_depth(size_t _depth) { depth = _depth; }

  virtual void accept(NodeVisitor *visitor) const {
    std::cout << "Address: " << this << " " << std::flush;
    throw std::logic_error("Trying to accept a visitor to Node (base class)");
  }
  virtual ~Node() = default;

private:
  Node *parent = nullptr;
  std::vector<Node *> children;
  bool _is_last = true;
  bool _is_leaf = true;

  size_t idx = 0;
  size_t depth = 0;
};

struct Operator : public Node {};

struct BinaryOperator final : public Operator {
  BinaryOperator(const BinaryOperatorEnum &op) : op{op} {}

  BinaryOperatorEnum op;

  void accept(NodeVisitor *visitor) const override { visitor->visit(this); }
};

struct UnaryOperator final : public Operator {
  UnaryOperator(const UnaryOperatorEnum &op) : op{op} {}
  UnaryOperatorEnum op;

  void accept(NodeVisitor *visitor) const override { visitor->visit(this); }
};

struct Number final : public Node {
  Number(const double &value) : value{value} {}
  double value;

  void accept(NodeVisitor *visitor) const override { visitor->visit(this); }
};

} // namespace ast
} // namespace paracl
