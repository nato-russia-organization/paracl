#pragma once

namespace paracl {
namespace ast {

struct BinaryOperator;
struct UnaryOperator;
struct Integer;
struct Float;
struct Double;

class NodeVisitor {

public:
  virtual void visit(const BinaryOperator *node) const = 0;
  virtual void visit(const UnaryOperator *node) const = 0;
  virtual void visit(const Integer *node) const = 0;
  virtual void visit(const Float *node) const = 0;
  virtual void visit(const Double *node) const = 0;

  virtual ~NodeVisitor() = default;
};

} // namespace ast
} // namespace paracl
