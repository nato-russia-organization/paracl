#pragma once

#include <istream>
#include <stdexcept>
#include <string>

#include "lexer_class.hpp"
#include <location/locationRange.hpp>

namespace paracl {
namespace driver {
class ParaclDriver final {

public:
  ParaclDriver(bool trace_scanning = false) : trace_scanning{trace_scanning} {}

  void parse(std::istream &iss) {
    if (!iss.good() && iss.eof()) {
      return;
    }

    delete (lexer);
    lexer = new paracl::ParaclLexer(&iss);

    delete (parser);
    parser = new paracl::ParaclParser(*this, loc, *lexer);

    if (parser->parse() != 0)
      throw std::runtime_error("Parse failed");

    return;
  }

  ~ParaclDriver() {
    delete (lexer);
    lexer = nullptr;
    delete (parser);
    parser = nullptr;
  }

private:
  paracl::ParaclParser *parser = nullptr;
  paracl::ParaclLexer *lexer = nullptr;

  bool trace_scanning;

  location_namespace::LocationRange loc;

  /** define some pretty colors **/
  const std::string red = "\033[1;31m";
  const std::string blue = "\033[1;36m";
  const std::string norm = "\033[0m";
};
} // namespace driver
} // namespace paracl
//
