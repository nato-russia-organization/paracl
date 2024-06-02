#include <syntax_tree/tree.hpp>

namespace paracl {
namespace ast {

enum class BinaryOperatorEnum { PLUS, MINUS, MULTIPLY, DIVIDE };

enum class UnaryOperatorEnum { MINUS };

class Operator : public Node {};

class BinaryOperator final : public Operator {
  BinaryOperatorEnum op;
};

class UnaryOperator final : public Operator {
  UnaryOperatorEnum op;
};

class Number : public Node {};

class Integer final : public Number {
  int value;
};

class Float final : public Number {
  float value;
};

class Double final : public Number {
  double value;
};

}; // namespace ast
}; // namespace paracl
