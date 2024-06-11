%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include <drivers/lexer_class.hpp>
#undef  YY_DECL
#define YY_DECL int paracl::ParaclLexer::yylex( paracl::ParaclParser::semantic_type * const lval, paracl::ParaclParser::location_type *location )

/* using "token" to make the returns for the tokens shorter to type */
using token = paracl::ParaclParser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%require "3.2"

%option debug
%option nodefault
%option yyclass="paracl::ParaclScanner"
%option noyywrap
%option c++

%define api.value.type variant

DIGIT    [0-9]
   
%%

"-"            {return MINUS;}
"+"            {return PLUS;}
"*"            {return MULT;}
"/"            {return DIV;}
"="            {return EQUAL;}
"("            {return L_PAREN;}
")"            {return R_PAREN;}

(\.{DIGIT}+)|({DIGIT}+(\.{DIGIT}*)?([eE][+-]?[0-9]+)?)   {
  yylval.dval = atof(yytext); 
  return NUMBER;
}

[ \t]+         {/* ignore spaces */}

"\n"           {return END;}

.              {printf("Error at line %d: unrecognized symbol \"%s\"\n", yylloc.first_line, yytext); exit(0);}
%%
