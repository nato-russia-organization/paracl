#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <vector>

namespace paracl {
namespace ast {

struct Node {
  void add_child(Node *child) {
    if (is_leaf) {
      is_leaf = false;
      child->is_last = true;
    } else {
      child->set_idx(children.back()->get_idx() + 1);
      children.back()->is_last = false;
    }

    child->set_parent(this);
    child->set_depth(depth + 1);
    children.push_back(child);
  }

  [[nodiscard]] const std::vector<Node *> get_children() const {
    return children;
  }
  const Node *get_parent() const { return parent; }
  [[nodiscard]] size_t get_idx() const { return idx; }
  [[nodiscard]] size_t get_depth() const { return depth; }

  const bool islast() const { return is_last; }
  const bool isleaf() const { return is_leaf; }

  void set_parent(Node *parent_node) { parent = parent_node; }
  void set_idx(size_t _idx) { idx = _idx; }
  void set_depth(size_t _depth) { depth = _depth; }

  virtual ~Node() = default;

private:
  Node *parent = nullptr;
  std::vector<Node *> children;
  bool is_last = true;
  bool is_leaf = true;

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

    Iterator(const Ast &ast) : node{ast.root} {}
    Iterator() : node{nullptr} {}
    Iterator(const Iterator &it) = default;

    const value_type operator*() const { return *node; }
    value_type operator*() { return *node; }
    bool operator==(const Iterator &rhs) const { return node == rhs.node; }

    Iterator &operator++() {
      if (!node->get_children().empty()) {
        node = node->get_children().front();
      } else {
        while (node->islast()) {
          node = node->get_parent();

          if (node->get_parent() == nullptr) {
            node = nullptr;
            return *this;
          }
        }

        node = (node->get_parent()->get_children())[node->get_idx() + 1];
      }

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

  Iterator begin() { return Iterator(*this); }
  Iterator end() { return Iterator(); }

private:
  std::vector<std::unique_ptr<Node>> nodes;
  Node *root;
};

}; // namespace ast
}; // namespace paracl
