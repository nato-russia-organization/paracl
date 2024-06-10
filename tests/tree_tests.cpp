#include <syntax_tree/dump_visitor.hpp>
#include <syntax_tree/interpret_visitor.hpp>
#include <syntax_tree/tree.hpp>
using namespace paracl::ast;

void dump(Node *root, DumpVisitor &v);
void test(Ast &ast, double val);
void interpret(Node *root, InterpretVisitor &v);

int main() {

  Ast ast(std::make_unique<BinaryOperator>(BinaryOperatorEnum::PLUS));

  test(ast, 1);
  test(ast, 2);

  auto root = ast.get_root();
  DumpVisitor v;
  InterpretVisitor i_v;
  dump(root, v);
  interpret(root, i_v);

  return 0;
}

void dump(Node *root, DumpVisitor &v) {

  root->accept(&v);

  for (auto &&x : root->get_children()) {
    x->accept(&v);
  }
}

void interpret(Node *root, InterpretVisitor &v) {
  for (auto &&x : root->get_children()) {
    x->accept(&v);
  }

  root->accept(&v);
  std::cout << "Result: " << v.get_result() << std::endl;
}

void test(Ast &ast, double val) {
  ast.add_child_to_node(*ast.get_root(), std::make_unique<Number>(val));
}
