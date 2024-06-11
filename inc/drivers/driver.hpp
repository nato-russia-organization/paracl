#pragma once

#include <cstddef>
#include <istream>
#include <string>

#include "lexer_class.hpp"

namespace paracl {

class ParaclDriver final {
public:
  ParaclDriver() = default;

  void parse(const char *filename);
  void parse(std::istream &iss);

  void add_upper();
  void add_lower();
  void add_word(const std::string &word);
  void add_newline();
  void add_char();

  std::ostream &print(std::ostream &stream);

private:
  void parse_helper(std::istream &stream);

  std::size_t chars = 0;
  std::size_t words = 0;
  std::size_t lines = 0;
  std::size_t uppercase = 0;
  std::size_t lowercase = 0;
  paracl::ParaclParser *parser = nullptr;
  paracl::ParaclLexer *lexer = nullptr;

  /** define some pretty colors **/
  const std::string red = "\033[1;31m";
  const std::string blue = "\033[1;36m";
  const std::string norm = "\033[0m";
};

} // namespace paracl
