#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <location.hh>
#include <parser.hpp>
#include <syntax_tree/tree.hpp>

namespace paracl {

class ParaclLexer final : public yyFlexLexer {
public:
  ParaclLexer(std::istream *in) : yyFlexLexer(in) {
    loc = new paracl::ParaclParser::location_type();
  };

  // get rid of override virtual function warning

  ParaclParser::symbol_type
  yylex(paracl::ParaclDriver &driver,
        paracl::ParaclParser::location_type &location);
  // YY_DECL defined in mc_lexer.l
  // Method body created by flex in mc_lexer.yy.cc

private:
  /* yyval ptr */
  paracl::ParaclParser::semantic_type *yylval = nullptr;
  /* location ptr */
  paracl::ParaclParser::location_type *loc = nullptr;
};
} // namespace paracl
