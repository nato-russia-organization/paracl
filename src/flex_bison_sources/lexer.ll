%{
/* C++ string header, for string ops below */
#include <string>
#include <syntax_tree/tree.hpp>
/* Implementation of yyFlexScanner */ 
#include <drivers/lexer_class.hpp>
#include <parser.hpp>

#undef YY_DECL
#define YY_DECL                                                                \
  paracl::ParaclParser::symbol_type paracl::ParaclLexer::yylex(paracl::driver::ParaclDriver &driver, paracl::ParaclParser::location_type &loc)

/* using "token" to make the returns for the tokens shorter to type */
using token = paracl::ParaclParser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( paracl::ParaclParser::make_END(loc) )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc.step(); loc.columns(yyleng);

%}

%option noyywrap nounput noinput batch
%option debug
%option yyclass="paracl::ParaclScanner"
%option c++


DIGIT    [0-9]
   
%%


"-"            {return paracl::ParaclParser::make_MINUS(loc);}
"+"            {return paracl::ParaclParser::make_PLUS(loc);}
"*"            {return paracl::ParaclParser::make_MUL(loc);}
"/"            {return paracl::ParaclParser::make_DIV(loc);}
"("            {return paracl::ParaclParser::make_LPAR(loc);}
")"            {return paracl::ParaclParser::make_RPAR(loc);}

(\.{DIGIT}+)|({DIGIT}+(\.{DIGIT}*)?([eE][+-]?[0-9]+)?)   {
  double val = atof(yytext); 
  return paracl::ParaclParser::make_NUMBER(val, loc);;
}

[ \t\n]+         {/* ignore spaces */}


.              {printf("Error at line SOMEWHERE: unrecognized symbol \"%s\"\n", yytext); exit(0);}
%%
