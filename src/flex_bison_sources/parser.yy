%skeleton "lalr1.cc"
%require  "3.2"
%defines 
%define api.namespace {paracl}
%define api.parser.class {ParaclParser}

%code requires{

   #include <cstddef>
   #include <iostream>
   #include <location/locationRange.hpp>
   
   #include <syntax_tree/tree.hpp>
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


%token <std::unique_ptr<paracl::ast::Ast>> NUMBER "number"
%token
  MINUS   "-"
  PLUS    "+"
  MUL    "*"
  DIV   "/"
  LPAR  "("
  RPAR  ")"
  END 0 "end of file"
;

%nterm <std::unique_ptr<paracl::ast::Ast>> expr
%nterm <std::unique_ptr<paracl::ast::Ast>> unit 
%left "+" "-"
%left "*" "/"

%%

%start unit;

unit : expr END { 
    $$ = std::move($1);
  };

expr:
   "number" {
    $$ = std::move($1);
   }
 | expr "+" expr { 
    std::vector<paracl::ast::Ast> trees;
    trees.push_back(std::move(*$1));
    trees.push_back(std::move(*$3));
  
    auto tree = paracl::ast::Ast::create_tree_from_root_and_subtrees(
        std::make_unique<paracl::ast::BinaryOperator>(paracl::ast::BinaryOperatorEnum::PLUS), std::move(trees));
  }

 | expr "-" expr {     
    std::vector<paracl::ast::Ast> trees;
    trees.push_back(std::move(*$1));
    trees.push_back(std::move(*$3));
  
    auto tree = paracl::ast::Ast::create_tree_from_root_and_subtrees(
        std::make_unique<paracl::ast::BinaryOperator>(paracl::ast::BinaryOperatorEnum::MINUS), std::move(trees));
  }

 | expr "*" expr { 
    std::vector<paracl::ast::Ast> trees;
    trees.push_back(std::move(*$1));
    trees.push_back(std::move(*$3));
  
    auto tree = paracl::ast::Ast::create_tree_from_root_and_subtrees(
        std::make_unique<paracl::ast::BinaryOperator>(paracl::ast::BinaryOperatorEnum::MUL), std::move(trees));
  }
 | expr "/" expr { 
    std::vector<paracl::ast::Ast> trees;
    trees.push_back(std::move(*$1));
    trees.push_back(std::move(*$3));
  
    auto tree = std::make_unique<paracl::ast::Ast>(paracl::ast::Ast::create_tree_from_root_and_subtrees(
        std::make_unique<paracl::ast::BinaryOperator>(paracl::ast::BinaryOperatorEnum::DIV), std::move(trees))); 
  }
 | "(" expr ")"  {
      $$ = std::move($2);
    };

%%


void 
paracl::ParaclParser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
