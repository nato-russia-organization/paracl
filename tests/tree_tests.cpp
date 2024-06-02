#include <syntax_tree/tree.hpp>

using namespace paracl::ast;
int main() {
  static_assert(std::forward_iterator<Ast::Iterator>);
  return 0;
}
