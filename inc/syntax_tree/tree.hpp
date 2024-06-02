#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <traversals/ast_base_postorder_traversal.hpp>
#include <vector>

namespace paracl {
namespace ast {

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

  virtual void accept(traversals::AstBasePostorderTraversal *visitor) const {
    throw std::logic_error("Can't accept the visitor for the base node");
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

class Ast {
public:
  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = const Node;
    using difference_type = ptrdiff_t;
    using pointer = const Node *;
    using reference = const Node &;

    Iterator(const Ast &ast) {
      node = ast.root;
      while (!node->is_leaf())
        node = node->get_children()[0];
    }
    Iterator() : node{nullptr} {}
    Iterator(const Iterator &it) = default;
    Iterator &operator=(const Iterator &it) = default;

    [[nodiscard]] const value_type operator*() const { return *node; }
    [[nodiscard]] value_type operator*() { return *node; }
    [[nodiscard]] bool operator==(const Iterator &rhs) const {
      return node == rhs.node;
    }

    Iterator &operator++() {
      if (node->is_last()) {
        node = node->get_parent();
      }

      node = (node->get_parent()->get_children())[node->get_idx() + 1];

      while (!node->is_leaf())
        node = node->get_children()[0];
      return *this;
    }

    Iterator operator++(int) {
      auto tmp = this;
      ++(*this);
      return *tmp;
    }

  private:
    pointer node;
  }; // Iterator END

  void add_child_to_node(Node &node, std::unique_ptr<Node> child) {
    node.add_child(child.get());
    nodes.push_back(std::move(child));
  }

  [[nodiscard]] Iterator begin() { return Iterator(*this); }
  [[nodiscard]] Iterator end() { return Iterator(); }

private:
  std::vector<std::unique_ptr<Node>> nodes;
  Node *root;
};

} // namespace ast
} // namespace paracl
