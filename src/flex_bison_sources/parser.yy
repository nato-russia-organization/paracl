%skeleton "lalr1.cc"
%require  "3.2"
%defines 
%define api.namespace {paracl}
%define api.parser.class {ParaclParser}

%code requires{
   namespace paracl {
      class ParaclDriver;
      class ParaclLexer;
      
      #include <cstddef>
      struct Location final {
        size_t line;
        size_t column;
      };

      struct LocationRange final {
        Location begin; 
        Location end;

        void step() {
          begin = end;
        }

        void columns(size_t width) {
          end.column += width;
        }

        void lines(size_t len) {
          end.line += len;
        }
      };

      #include <iostream>
      std::ostream& operator<< (std::ostream& os, const LocationRange& loc) {
        os << "From: (" << loc.begin.line << ", " << loc.begin.column << "); " 
           << "To: (" << loc.end.line << ", " << loc.end.column << ")"; 
        return os;
      }

   }
}

%param { ParaclDriver  &driver  }
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

%define api.location.type {paracl::LocationRange}
%locations


%token <double> NUMBER "number"
%token
  MINUS   "-"
  PLUS    "+"
  MUL    "*"
  DIV   "/"
  LPAR  "("
  RPAR  ")"
  END "<<EOF>>"
;

%nterm <double> expr
%nterm <double> unit 
%left "+" "-"
%left "*" "/"

%%

%start unit;

unit : expr {};

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
