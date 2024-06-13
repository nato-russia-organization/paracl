#include "syntax_tree/node.hpp"
#include "syntax_tree/tree.hpp"
#include <aux/test_interpret.hpp>
#include <gtest/gtest.h>

using namespace paracl::ast;

TEST_F(TreeTest, Addition) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(0));

  EXPECT_EQ(interpret(tree.get_root()), 3);
}

TEST_F(TreeTest, Multiplication) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::MUL));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(0));

  EXPECT_EQ(interpret(tree.get_root()), 0);
}

TEST_F(TreeTest, Division) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::DIV));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(1));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));

  EXPECT_EQ(interpret(tree.get_root()), 1.0 / 3);
}

TEST_F(TreeTest, Subtraction) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::MINUS));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(1));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));

  EXPECT_EQ(interpret(tree.get_root()), 1 - 3);
}

TEST_F(TreeTest, Subtraction_2) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::MINUS));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(6));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));

  EXPECT_EQ(interpret(tree.get_root()), 3);
}

TEST_F(TreeTest, AdditionSubtraction) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));
  auto minus = tree.add_child_to_node(
      *tree.get_root(),
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::MINUS));
  tree.add_child_to_node(*minus, std::make_unique<Number>(0));
  tree.add_child_to_node(*minus, std::make_unique<Number>(1));

  EXPECT_EQ(interpret(tree.get_root()), 2);
}

TEST_F(TreeTest, DivisionByZero) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));
  auto div = tree.add_child_to_node(
      *tree.get_root(),
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::DIV));
  tree.add_child_to_node(*div, std::make_unique<Number>(1));
  tree.add_child_to_node(*div, std::make_unique<Number>(0));

  EXPECT_THROW(interpret(tree.get_root()), std::logic_error);
}

TEST_F(TreeTest, EverythingEverywhere) {
  tree.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));
  tree.add_child_to_node(*tree.get_root(), std::make_unique<Number>(3));
  auto div = tree.add_child_to_node(
      *tree.get_root(),
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::DIV));
  auto mul = tree.add_child_to_node(
      *tree.get_root(),
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::MUL));
  auto sub = tree.add_child_to_node(
      *mul, std::make_unique<BinaryOperator>(BinaryOperatorEnum::MINUS));
  tree.add_child_to_node(*div, std::make_unique<Number>(1));
  tree.add_child_to_node(*div, std::make_unique<Number>(2));
  tree.add_child_to_node(*mul, std::make_unique<Number>(7));
  tree.add_child_to_node(*sub, std::make_unique<Number>(8));
  tree.add_child_to_node(*sub, std::make_unique<Number>(1));

  EXPECT_EQ(interpret(tree.get_root()), 49.5);
}

TEST_F(TreeTest, StaticConstructor) {
  Ast tree1;
  tree1.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));
  tree1.add_child_to_node(*tree1.get_root(), std::make_unique<Number>(3));
  auto div1 = tree1.add_child_to_node(
      *tree1.get_root(),
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::DIV));
  auto mul1 = tree1.add_child_to_node(
      *tree1.get_root(),
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::MUL));
  auto sub1 = tree1.add_child_to_node(
      *mul1, std::make_unique<BinaryOperator>(BinaryOperatorEnum::MINUS));
  tree1.add_child_to_node(*div1, std::make_unique<Number>(1));
  tree1.add_child_to_node(*div1, std::make_unique<Number>(2));
  tree1.add_child_to_node(*mul1, std::make_unique<Number>(7));
  tree1.add_child_to_node(*sub1, std::make_unique<Number>(8));
  tree1.add_child_to_node(*sub1, std::make_unique<Number>(1));

  Ast tree2;
  tree2.add_root(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));
  tree2.add_child_to_node(*tree2.get_root(), std::make_unique<Number>(3));
  auto minus2 = tree2.add_child_to_node(
      *tree2.get_root(),
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::MINUS));
  tree2.add_child_to_node(*minus2, std::make_unique<Number>(0));
  tree2.add_child_to_node(*minus2, std::make_unique<Number>(1));

  std::vector<Ast> trees;
  trees.push_back(std::move(tree1));
  trees.push_back(std::move(tree2));

  tree = Ast::create_tree_from_root_and_subtrees(
      std::make_unique<BinaryOperator>(BinaryOperatorEnum::MUL), trees);

  EXPECT_EQ(interpret(tree.get_root()), 99);
}
