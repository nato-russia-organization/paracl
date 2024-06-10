#pragma once

namespace paracl {
namespace ast {

struct BinaryOperator;
struct UnaryOperator;
struct Number;

class NodeVisitor {

public:
  virtual void visit(const BinaryOperator *node) = 0;
  virtual void visit(const UnaryOperator *node) = 0;
  virtual void visit(const Number *node) = 0;

  virtual ~NodeVisitor() = default;
};

} // namespace ast
} // namespace paracl
