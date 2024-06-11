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
