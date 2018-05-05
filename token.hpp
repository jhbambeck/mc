#pragma once
#include <iostream>
#include <iomanip>
#include <bitset>
#include "symbol.hpp"

enum token_name 
{
  //punctuators
  tok_left_brace, 
  tok_right_brace, 
  tok_left_paren, 
  tok_right_paren, 
  tok_left_bracket, 
  tok_right_bracket, 
  tok_comma, 
  tok_semicolon, 
  tok_colon, 
  
  //operators
  tok_relational_operator, 
  tok_arithmetic_operator, 
  tok_bitwise_operator, 
  tok_conditional_operator, 
  tok_assignment_operator,
  tok_arrow, 
  
  //keywords
  kw_bool, 
  kw_char,
  kw_def, 
  kw_else, 
  kw_false, 
  kw_float, 
  kw_if, 
  kw_int, 
  kw_let,
  kw_true, 
  kw_var,
  kw_and, 
  kw_or,
  kw_not,
  kw_as, 
  kw_return, 
  kw_void, 
  kw_while, 
  kw_const, 
  kw_volatile,
  kw_continue, 
  kw_break, 

  //identifiers
  tok_identifier, 
  
  //literals
  tok_decimal_integer_literal,
  tok_hexadecimal_integer_literal, 
  tok_binary_integer_literal, 
  tok_floating_point_literal, 
  tok_boolean_literal,
  tok_character_literal, 
  tok_string_literal, 
  
  //eof
  tok_end_of_file, 
  is_false, 
};

enum relational_operator_kind
{
  equal, 
  not_equal,
  less_than, 
  greater_than, 
  less_than_or_equal_to, 
  greater_than_or_equal_to, 
};

enum arithmetic_operator_kind
{
  add, 
  subtract, 
  multiply, 
  divide, 
  modulo, 
};

enum bitwise_operator_kind 
{
  bitwise_and, 
  bitwise_or, 
  bitwise_complement, 
  bitwise_xor,
  bitwise_not,   
};

union token_attribute
{
  relational_operator_kind rel_op;
  arithmetic_operator_kind arith_op;
  bitwise_operator_kind bit_op;
  int intval;
  symbol sym;
  char* stringval; 
  double doubleval;   
};

struct token 
{
  token_name name; 
  token_attribute attribute;
  token() 
    { name = is_false; }
  token(token_name n)
    { name = n; } 
  token(token_name n, token_attribute a)
    : name{n}, attribute{a} {}
  operator bool() const {return name != is_false;}
   
};

void print_token(token);
std::string inttobinstring(int);  
