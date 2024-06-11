#pragma once

#include <concepts>
#include <gtest/gtest.h>
#include <syntax_tree/dump_visitor.hpp>
#include <syntax_tree/interpret_visitor.hpp>
#include <syntax_tree/tree.hpp>

using namespace paracl::ast;

class TreeTest : public testing::Test {
protected:
  Ast tree;
  InterpretVisitor v;
  DumpVisitor d;

public:
  void dump(Node *node) {

    node->accept(&d);

    for (auto &&x : node->get_children()) {
      x->accept(&d);
    }
  }

  double interpret(Node *node) {
    for (auto &&x : node->get_children()) {
      interpret(x);
    }

    node->accept(&v);
    return v.get_result();
  }

  template <typename NodeType>
    requires std::derived_from<NodeType, Node>
  void add_child(Node &append_to, std::unique_ptr<NodeType> node_to_append) {
    tree.add_child_to_node(append_to, node_to_append);
  }
};
