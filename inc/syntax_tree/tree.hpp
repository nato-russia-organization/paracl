#pragma once

#include <concepts>
#include <memory>
#include <syntax_tree/node.hpp>
#include <vector>

namespace paracl {
namespace ast {

class Ast {
public:
  template <typename NodeType>
    requires std::derived_from<NodeType, Node>
  Node *add_child_to_node(Node &node, std::unique_ptr<NodeType> &&child) {
    node.add_child(child.get());
    nodes.push_back(std::move(child));
    return node.get_children().back();
  }

  template <typename NodeType>
    requires std::derived_from<NodeType, Node>
  Node *add_root(std::unique_ptr<NodeType> &&root_up) {
    root = root_up.get();
    nodes.push_back(std::move(root_up));
    return root;
  }

  Ast() = default;

  template <typename NodeType>
    requires std::derived_from<NodeType, Node>
  Ast(std::unique_ptr<NodeType> &&root) : root{root.get()} {
    nodes.push_back(std::move(root));
  }

  Node *get_root() { return root; }

private:
  std::vector<std::unique_ptr<Node>> nodes;
  Node *root;
};

} // namespace ast
} // namespace paracl
