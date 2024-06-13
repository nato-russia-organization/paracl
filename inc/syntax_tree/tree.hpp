#pragma once

#include <algorithm>
#include <concepts>
#include <iterator>
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

  // constructor that creates a tree given it's root and subtrees

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

  [[nodiscard]] Node *get_root() { return root; }

  template <typename NodeType>
    requires std::derived_from<NodeType, Node>
  [[nodiscard]] static Ast
  create_tree_from_root_and_subtrees(std::unique_ptr<NodeType> &&root,
                                     std::vector<Ast> &trees) {
    Ast ast(std::move(root));

    ast.valid_node_aux_data = false;

    for (auto &&tree : trees) {
      ast.nodes.insert(ast.nodes.end(),
                       std::make_move_iterator(tree.nodes.begin()),
                       std::make_move_iterator(tree.nodes.end()));

      Node *tree_root = tree.root;
      tree.root = nullptr;

      ast.root->add_child(tree_root);
    }

    return ast;
  }

private:
  std::vector<std::unique_ptr<Node>> nodes;
  Node *root;
  bool valid_node_aux_data =
      false; // checks wether data about node depths is valid, no method to
             // calulate it is yet created, didn't need it
};

} // namespace ast
} // namespace paracl
