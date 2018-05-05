#pragma once
#include <string>
#include <cassert>
#include <math.h>
#include "token.hpp"
#include "symbol.hpp"

struct lexer
{
  lexer(symbol_table& stbl, const std::string& str) 
    : first(str.data()), last(first + str.size())
    { syms = &stbl; } 
  token lex();
  token lex_rel_assign_operator();
  token lex_arithmetic_operator(); // and arrow for now
  token lex_bitwise_operator();
  token lex_conditional_operator();
  token lex_punctuator();
  token lex_number();
  token lex_floating_point();
  token lex_hexadecimal(); 
  token lex_binary();   
  token lex_decimal();
  token lex_identifier_keyword();
  token lex_keyword(std::string&);
  token lex_identifier(std::string&);
  token lex_string();
  void lex_comment();    
  bool ishexdigit(char);
  bool isbinarydigit(char);
  bool isnondigit(char);
  bool iskeyword(std::string&);
  bool isstringchar(char, bool);       
  bool eof() 
    {return first >= last;}
  char peek(int);
  char accept();
  void ignore(); 
  
  const char* first;
  const char* last;
  const char* token_loc;
  symbol_table* syms;    
};
