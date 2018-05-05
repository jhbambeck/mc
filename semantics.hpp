#pragma once
#include <unordered_map>
#include "statement.hpp"
#include "expr.hpp"
#include "type.hpp"
#include "token.hpp"
#include "decl.hpp"

struct semantics 
{
  std::unordered_map<symbol, decl*> name_map; 
  
  type* on_basic_type(token);
  
  expr* on_integer_literal(token);
  expr* on_boolean_literal(token);
  expr* on_float_literal(token); 
  expr* on_id_expression(type*, decl*);
  expr* on_id_as_primary(symbol);
  //expr* on_unary_expression(token, expr*); 
  expr* on_additive_expression(token, expr*, expr*);
  expr* on_multiplicative_expression(token, expr*, expr*);
  expr* on_relational_expression(type*, binop, expr*, expr*);
  expr* on_equality_expression(type*, binop, expr*, expr*); 
  
  decl* on_value_decl(symbol, type*, expr*); 
  decl* on_parm_decl(symbol, type*);

  stmt* on_declaration_statement(decl*);
  stmt* on_expression_statement(expr*);
  stmt* on_block_statement(stmt_list&);
  stmt* on_while_statement(expr*, stmt*);
  stmt* on_if_statement(expr*, stmt*, stmt*);
  stmt* on_assignment_statement(symbol, expr*); 
};
