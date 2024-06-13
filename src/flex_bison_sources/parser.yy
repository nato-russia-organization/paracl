%skeleton "lalr1.cc"
%require  "3.2"
%defines 
%define api.namespace {paracl}
%define api.parser.class {ParaclParser}

%code requires{

   #include <cstddef>
   #include <iostream>
   #include <location/locationRange.hpp>
   
   namespace paracl {
      namespace driver {
        class ParaclDriver;
      }

      class ParaclLexer;

   }
}

%param { driver::ParaclDriver  &driver  }
%param { location_type &loc}
%parse-param { ParaclLexer &lexer }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   #include <drivers/lexer_class.hpp> 
   #include <syntax_tree/tree.hpp>
    
#undef yylex
#define yylex lexer.yylex
}

%define api.value.type variant
%define parse.assert
%define api.token.raw
%define api.token.constructor
%define parse.trace
%define parse.error detailed
%define parse.lac full
%define api.token.prefix {TOK_}

%define api.location.type {paracl::location_namespace::LocationRange}
%locations


%token <double> NUMBER "number"
%token
  MINUS   "-"
  PLUS    "+"
  MUL    "*"
  DIV   "/"
  LPAR  "("
  RPAR  ")"
  END 0 "end of file"
;

%nterm <double> expr
%nterm <double> unit 
%left "+" "-"
%left "*" "/"

%%

%start unit;

unit : expr END { std::cout << "Result: " << $1 << std::endl; };

expr:
   "number"
 | expr "+" expr { $$ = $1 + $3; }
 | expr "-" expr { $$ = $1 - $3; }
 | expr "*" expr { $$ = $1 * $3; }
 | expr "/" expr { $$ = $1 / $3; }
 | "(" expr ")"  { $$ = $2; };

%%


void 
paracl::ParaclParser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
