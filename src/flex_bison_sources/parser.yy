%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {paracl}
%define api.parser.class {ParaclParser}

%code requires{
   namespace paracl {
      class ParaclDriver;
      class ParaclLexer;
   }
}

%parse-param { ParaclLexer  &lexer  }
%parse-param { ParaclDriver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include <drivers/driver.hpp>
   #include <drivers/lexer_class.hpp> 
#undef yylex
#define yylex lexer.yylex
}

%define api.value.type variant
%define parse.assert

%token               END    0     "end of file"
%token               UPPER
%token               LOWER
%token <std::string> WORD
%token               NEWLINE
%token               CHAR

%locations

%%

list_option : END | list END;

list
  : item
  | list item
  ;

item
  : UPPER   { driver.add_upper(); }
  | LOWER   { driver.add_lower(); }
  | WORD    { driver.add_word( $1 ); }
  | NEWLINE { driver.add_newline(); }
  | CHAR    { driver.add_char(); }
  ;

%%


void 
paracl::ParaclParser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
