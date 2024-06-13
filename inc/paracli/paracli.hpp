#pragma once

#include <drivers/driver.hpp>
#include <syntax_tree/interpret_visitor.hpp>
#include <syntax_tree/tree.hpp>

namespace paracl {
namespace interpreter {

class Interpreter {
public:
  Interpreter(std::istream &iss, bool trace_scanning = false)
      : driver{trace_scanning}, iss{iss} {}

  void run() { driver.parse(iss); }

private:
  ast::InterpretVisitor visitor;
  ast::Ast tree;
  driver::ParaclDriver driver;
  std::istream &iss;
};

} // namespace interpreter
} // namespace paracl
