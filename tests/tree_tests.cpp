#include <syntax_tree/dump_visitor.hpp>
#include <syntax_tree/tree.hpp>
using namespace paracl::ast;

void dump(Node *root, DumpVisitor &v);
void test(Ast &ast, double val);

int main() {

  Ast ast(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));

  test(ast, 1);
  test(ast, 2);

  auto root = ast.get_root();
  DumpVisitor v;

  dump(root, v);

  return 0;
}

void dump(Node *root, DumpVisitor &v) {

  root->accept(&v);

  for (auto &&x : root->get_children()) {
    std::cout << "accepting to " << x << std::endl;
    x->accept(&v);
  }
}

void test(Ast &ast, double val) {
  ast.add_child_to_node(*ast.get_root(), std::make_unique<Double>(val));
}
