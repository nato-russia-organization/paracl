#pragma once

#include <syntax_tree/tree.hpp>
namespace paracl {
namespace traversals {

class AstBasePostorderTraversal {

public:
  ~AstBasePostorderTraversal() = default;

  AstBasePostorderTraversal(Iterator begin, Iterator end) {}

  void traverse() {
    auto ite = _end;
    for (auto it = _begin; it != ite; ++it) {
    }
  }

private:
  Iterator _begin;
  Iterator _end;
};

} // namespace traversals
} // namespace paracl
