#pragma once
#include "lexer.hpp"
#include "semantics.hpp"

struct parser
{
  parser(symbol_table &syms, const std::string& file_string)
    : lex(syms, file_string) { accept(); } 

  stmt* parse(); 

private: 
  token current_tok; 
  lexer lex; 
  semantics act; 
   
  token accept();
  token match(token_name);
  token match_if(token_name); 
  token match_if_arith_op(arithmetic_operator_kind);
  token match_if_bit_op(bitwise_operator_kind);
  token match_if_rel_op(relational_operator_kind);

  expr* parse_expression();
  //void parse_constant_expression(); 
  expr* parse_primary_expression(); 
  //void parse_postfix_expression();  
  //void parse_argument(); 
  //void parse_argument_list();  
  //void parse_unary_expression();
  //void parse_type_list(); 
  //void parse_basic_type(); 
  //void parse_postfix_type();  
  //void parse_reference_type();
  //void parse_type(); 
  type* parse_basic_type(); 
  //void parse_cast_expression(); 
  expr* parse_multiplicative_expression();  
  expr* parse_additive_expression(); 
  //void parse_shift_expression();//lex <<, >>
  expr* parse_relational_expression(); 
  expr* parse_equality_expression();  
  //void parse_bitwise_and_expression();
  //void parse_bitwise_xor_expression(); 
  //void parse_bitwise_or_expression(); 
  //void parse_logical_and_expression(); 
  //void parse_logical_or_expression(); 
  //void parse_conditional_expression(); 
  //void parse_assignment_expression(); 
 
  stmt*  parse_if_statement(); //if it's a statement  
  //token parse_if_return_statement(); 
  //token parse_if_continue_statement();//lex continue 
  //token parse_if_break_statement();//lex break
  stmt* parse_if_while_statement();
  stmt* parse_if_if_statement();   
  //token parse_if_statement_seq(); 
  stmt* parse_if_block_statement(); 
  stmt* parse_if_expression_statement();
  stmt* parse_if_declaration_statement();
  stmt* parse_if_assignment_statement();  

  decl* parse_function_definition();  
  //void parse_constant_definition(); 
  decl* parse_variable_definition(); 
  decl* parse_parameter();
  decl_list parse_parameter_list();  
  //void parse_local_declaration();
  //void parse_declaration(); 
  //void parse_declaration_seq();//expects end of file
  expr* parse_program();  
};
