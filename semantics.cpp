#include "semantics.hpp"

type* semantics::on_basic_type(token tok)
{
  type* t; 
  switch(tok.name)
  {
  case tok_decimal_integer_literal:
  case tok_hexadecimal_integer_literal: 
  case tok_binary_integer_literal:
  case kw_int: 
   t = new int_type; 
   break; 
  case tok_floating_point_literal: 
  case kw_float:
    t = new float_type;
    break; 
  case tok_boolean_literal:
  case kw_true: 
  case kw_false:
  case kw_bool: 
    t = new bool_type; 
    break; 
  case tok_character_literal: 
    t = new char_type; 
    break; 
  case tok_string_literal:  
  default: 
    throw std::runtime_error("Not basic type.");
  }
  return t; 
}

expr* semantics::on_integer_literal(token tok)
{
  expr* e = new int_expr(on_basic_type(tok), tok.attribute.intval);
  return e; 
}

expr* semantics::on_boolean_literal(token tok)
{
  expr* e = new bool_expr(on_basic_type(tok), tok.name == kw_true);
  return e; 
}

expr* semantics::on_float_literal(token tok)
{
  expr* e = new float_expr(on_basic_type(tok), tok.attribute.doubleval);
  return e; 
}

expr* semantics::on_id_expression(type* t, decl* d)
{
   expr* e = new id_expr(t, d);
   return e; 
}

/*
expr* semantics::on_unary_expression(token tok, expr* e)
{
  expr* e; 
  if(tok.name == tok_bitwise_operator)
  {
    if(tok.attribute.bit_op == bitwise_complement)
      e = new unop_expr(unop_cmp, e);
    else if(tok.attribute.bit_op == bitwise_not)
      e = new unop_expr(unop_not, e);
    else if(tok.attribute.bit_op == bitwise_and)
      e = new unop_expr(unop_addr, e); 
  }  
  else if(tok.name == tok_arithmetic_operator)
  {
    assert(tok.attribute.arith_op == multiply);
    e = new unop_expr(unop_dref, e);
  }
  else throw std::runtime_error("Bad token for unary expresssion.")
  return e; 
}
*/
expr* semantics::on_additive_expression(token tok, expr* e1, expr* e2)
{
  expr* e;
  if(tok.name == tok_arithmetic_operator && tok.attribute.arith_op == add)
  {
    e = new binop_expr(e1->t, binop_add, e1, e2);
    return e; 
  }
  else if(tok.name == tok_arithmetic_operator && tok.attribute.arith_op == subtract)
  {
    e = new binop_expr(e1->t, binop_sub, e1, e2);
    return e; 
  }
  else throw std::runtime_error("Bad token for additive expression.");
}

expr* semantics::on_multiplicative_expression(token tok, expr* e1, expr* e2)
{
  expr* e; 
  if(tok.name == tok_arithmetic_operator && tok.attribute.arith_op == multiply)
  {
    e = new binop_expr(e1->t, binop_mul, e1, e2);
    return e; 
  }
  else if(tok.name == tok_arithmetic_operator && tok.attribute.arith_op == divide)
  {
    e = new binop_expr(e1->t, binop_div, e1, e2); 
    return e; 
  }
  else if(tok.name == tok_arithmetic_operator && tok.attribute.arith_op == modulo)
  {
    e = new binop_expr(e1->t, binop_rem, e1, e2);
    return e; 
  }
  else throw std::runtime_error("Bad token for multiplicative expression.");
}

expr* semantics::on_relational_expression(type* t, binop bo, expr* e1, expr* e2)
{
  expr* e = new binop_expr(t, bo, e1, e2);
  return e; 
}

expr* semantics::on_equality_expression(type* t, binop bo, expr* e1, expr* e2)
{
  expr* e = new binop_expr(t, bo, e1, e2);
  return e; 
}

expr* semantics::on_id_as_primary(symbol sym)
{
  decl* d; 
  try 
  {
  d = name_map.at(sym);
  }
  catch(...)
  {
    throw std::runtime_error("undeclared identifier.");
  }
  expr* e = static_cast<value_decl*>(d)->init; 
  return e; 
}

// decls

decl* semantics::on_value_decl(symbol sym, type* t, expr* e = nullptr)
{ 
  decl* d =  new value_decl(sym, t, e); 
  std::pair<symbol, decl*> p(sym, d); 
  name_map.insert(p); 
  return d; 
}

decl* semantics::on_parm_decl(symbol sym, type* t)
{
  return new parm_decl(sym, t);
}

// stmts

stmt* semantics::on_expression_statement(expr* e)
{ 
  stmt* s = new expr_stmt(e); 
  return s; 
}

stmt* semantics::on_declaration_statement(decl* d)
{
  stmt* s = new decl_stmt(d);
  return s; 
}

stmt* semantics::on_block_statement(stmt_list& sl)
{
  stmt* s= new block_stmt(sl);
  return s; 
}

stmt* semantics::on_while_statement(expr* c, stmt* s)
{
  stmt* s_ = new while_stmt(c,s);
  return s_; 
}

stmt* semantics::on_if_statement(expr* c, stmt* s1, stmt* s2)
{
  stmt* s = new if_stmt(c, s1, s2);
  return s; 
}

stmt* semantics::on_assignment_statement(symbol s, expr* e)
{
  try
  {
    name_map.at(s);
  }
  catch (...)
  {
    throw std::runtime_error("undeclared identifier.");
  }
  return new assign_stmt(s,e);
}
