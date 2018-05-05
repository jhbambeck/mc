#include "parser.hpp"

stmt* parser::parse()
{
  stmt* s; 
  while(current_tok.name != tok_end_of_file) s = parse_if_statement(); 
  return s;  
  //parse_program(); 
}

token parser::accept()
{
  token temp = current_tok;  
  current_tok = lex.lex();
  print_token(current_tok); std::cout << '\n'; 
  return temp; 
}

token parser::match(token_name n)
{
  if(current_tok.name == n) return accept(); 
  else throw std::runtime_error("syntax error");
}

token parser::match_if(token_name n)
{
  if(current_tok.name == n) 
  {
    return accept(); 
  }
  return token(is_false);  
}

token parser::match_if_arith_op(arithmetic_operator_kind k)
{
  if(current_tok.name != tok_arithmetic_operator) return token(is_false); 
  if(current_tok.attribute.arith_op == k)
  {
    return accept(); 
  }
  return token(is_false); 
}

token parser::match_if_bit_op(bitwise_operator_kind k)
{
  if(current_tok.name != tok_bitwise_operator) return token(is_false); 
  if(current_tok.attribute.bit_op == k)
  {
    return accept(); 
  }
  return token(is_false); 
}

token parser::match_if_rel_op(relational_operator_kind k)
{
  if(current_tok.name != tok_relational_operator) return token(is_false); 
  if(current_tok.attribute.rel_op == k)
  {
    return accept(); 
  }
  return token(is_false); 
}

expr* parser::parse_expression()
{
    expr* e = parse_equality_expression(); 
    return e; 
}
/*
void parser::parse_constant_expression()
{
  parse_conditional_expression(); 
}
*/
expr* parser::parse_primary_expression()
{
  expr* e;
  symbol s;  
  switch(current_tok.name)
  {
  case tok_binary_integer_literal:
  case tok_decimal_integer_literal: 
  case tok_hexadecimal_integer_literal:
    e = act.on_integer_literal(current_tok);
    accept(); 
    break;  
  case tok_boolean_literal: 
    e = act.on_boolean_literal(current_tok);
    accept(); 
    break; 
  case tok_floating_point_literal: 
    e = act.on_float_literal(current_tok);
    accept(); 
    break; 
  //case tok_character_literal: 
  //case tok_string_literal:
  case kw_true: 
  case kw_false:
    e = act.on_boolean_literal(current_tok);
    accept(); 
    break; 
  
  case tok_identifier: 
    s = current_tok.attribute.sym; 
    e = act.on_id_as_primary(s); 
    accept(); 
    break;

 /*
  case tok_left_paren:
    match(tok_left_paren);
    parse_expression(); 
    match(tok_right_paren);
    break;
  */
  default: 
    throw std::runtime_error("expected primary expression"); 
  }
  return e; 
}
/*
void parser::parse_postfix_expression()
{
  parse_primary_expression(); 
  if(match_if(tok_left_paren))
  {
    if(match_if(tok_right_paren));
    else 
    {
      parse_argument_list(); 
      match(tok_right_paren); 
    }  
  }

  if(match_if(tok_left_bracket))
  {
    if(match_if(tok_right_bracket));
    else 
    {
      parse_argument_list(); 
      match(tok_right_bracket);
    } 
  }
}

void parser::parse_argument()
{
  parse_expression(); 
}

void parser::parse_argument_list() 
{
  parse_argument(); 
  while(match_if(tok_comma))
    parse_argument(); 
}

void parser::parse_unary_expression()
{
  bool cont = true; 
  parse_postfix_expression(); 
  while(cont)
  { 
    cont = false; 
    if(match_if_arith_op(add)) cont = true; 
    else if(match_if_arith_op(subtract)) cont = true; 
    else if(match_if_arith_op(multiply)) cont = true; 
    else if(match_if_bit_op(bitwise_complement)) cont = true; 
    else if(match_if_bit_op(bitwise_and)) cont = true;
    else if(match_if_bit_op(bitwise_not)) cont = true;  
    if(cont) parse_postfix_expression();
  }
}

void parser::parse_type_list()
{
  parse_type(); 
  while(match_if(tok_comma)) parse_type(); 
}
*/
type* parser::parse_basic_type()
{
  return act.on_basic_type(current_tok); 
  /*
  if(match_if(kw_void));
  else if(match_if(kw_bool));
  else if(match_if(kw_int));
  else if(match_if(kw_float));
  else if(match_if(kw_char));
  else if(match_if(tok_left_paren))
  {
    if(match_if(tok_right_paren)); 
    else 
    {
      parse_type_list(); 
      if(current_tok.name == tok_right_paren) accept();
      else throw std::runtime_error("expected right paren"); 
    }   
  } 
  else throw std::runtime_error("expected basic type"); */
}

/*
void parser::parse_postfix_type()
{
  parse_basic_type();   
  if(match_if(kw_const));
  else if(match_if(kw_volatile));
  else if(match_if(tok_left_bracket))
  {
    if(match_if(tok_right_bracket));
    else 
    {
      parse_expression(); 
      if(current_tok.name == tok_right_bracket) accept(); 
      else throw std::runtime_error("expected right bracket");
    }
  }
  match_if_bit_op(bitwise_and); // references?
}

void parser::parse_reference_type()
{
  parse_postfix_type();
  // reference handled in postfix for now
}

void parser::parse_type() 
{
  parse_reference_type(); 
}

void parser::parse_cast_expression()
{
  parse_unary_expression();  
  if(match_if(kw_as)) parse_type(); 
}
*/
expr* parser::parse_multiplicative_expression()
{
  token tok; 
  tok.name = tok_arithmetic_operator; 
  expr* e1 = parse_primary_expression(); 
  bool cont = true;
  while(cont)
  {
    cont = false; 
    if(match_if_arith_op(multiply))
    {
      tok.attribute.arith_op = multiply;
      cont = true;  
    }
    else if(match_if_arith_op(divide))
    {
      tok.attribute.arith_op = divide; 
      cont = true; 
    }
    else if(match_if_arith_op(modulo))
    {
      tok.attribute.arith_op = modulo; 
      cont = true; 
    }
    if(cont)
    {
      expr* e2 = parse_primary_expression(); 
      e1 = act.on_multiplicative_expression(tok, e1, e2);
    }
  }
  return e1; 
  /*
  parse_cast_expression(); 
  bool cont = true; 
  while(cont)
  {
    cont = false; 
    if(match_if_arith_op(multiply)) cont = true; 
    else if(match_if_arith_op(divide)) cont = true; 
    else if(match_if_arith_op(modulo)) cont = true; 
    if(cont) parse_cast_expression();  
  }*/
}

expr* parser::parse_additive_expression()
{
  token tok; 
  expr* e1 = parse_multiplicative_expression(); 
  bool cont = true; 
  while(cont)
  {
    cont = false; 
    if(match_if_arith_op(add)) 
    {
      tok.name = tok_arithmetic_operator; 
      tok.attribute.arith_op = add; 
      cont = true; 
    }
    else if(match_if_arith_op(subtract)) 
    {
      tok.name = tok_arithmetic_operator; 
      tok.attribute.arith_op = subtract; 
      cont = true; 
    }
    if(cont) 
    {
      expr* e2 = parse_multiplicative_expression();
      e1 = act.on_additive_expression(tok, e1, e2); 
    }
  }
  return e1; 
}
/*
void parser::parse_shift_expression()
{
  //need to lex << >> 
  parse_additive_expression(); 
}
*/
expr* parser::parse_relational_expression()
{
  expr* e1 = parse_additive_expression(); 
  expr* e2 = nullptr; 
  binop op = binop_; 
  if(match_if_rel_op(less_than)) op = binop_lt; 
  else if(match_if_rel_op(greater_than)) op = binop_gt; 
  else if(match_if_rel_op(less_than_or_equal_to)) op = binop_le; 
  else if(match_if_rel_op(greater_than_or_equal_to)) op = binop_ge; 
  if(op != binop_) e2 = parse_additive_expression();
  return act.on_relational_expression(e1->t, op, e1, e2);
}

expr* parser::parse_equality_expression()
{
  expr* e1 = parse_relational_expression(); 
  expr* e2 = nullptr; 
  binop op = binop_; 
  if(match_if_rel_op(equal)) op = binop_eq; 
  else if(match_if_rel_op(not_equal)) op = binop_ne; 
  if(op != binop_) e2 = parse_relational_expression();
  return act.on_equality_expression(e1->t, op, e1, e2); 
}
/*
void parser::parse_bitwise_and_expression()
{
  parse_equality_expression(); // instead of relational? 
  while(match_if_bit_op(bitwise_and)) parse_equality_expression();
}

void parser::parse_bitwise_xor_expression()
{
  parse_bitwise_and_expression(); 
  while(match_if_bit_op(bitwise_xor)) parse_bitwise_and_expression(); 
}

void parser::parse_bitwise_or_expression()
{
  parse_bitwise_xor_expression(); 
  while(match_if_bit_op(bitwise_or)) parse_bitwise_xor_expression(); 
}

void parser::parse_logical_and_expression()
{
  parse_bitwise_or_expression(); 
  while(match_if(kw_and)) parse_bitwise_or_expression(); 
}

void parser::parse_logical_or_expression()
{
  parse_logical_and_expression(); 
  while(match_if(kw_or)) parse_logical_and_expression(); 
}

void parser::parse_conditional_expression()
{
  parse_logical_or_expression(); 
  while(match_if(tok_conditional_operator))
  {
    parse_expression();
    match(tok_colon);
    parse_logical_or_expression(); 
  }
}

void parser::parse_assignment_expression()
{
  parse_conditional_expression();
  if(match_if(tok_assignment_operator))
    parse_conditional_expression(); 
}
*/
//statements

stmt* parser::parse_if_statement()
{
  stmt* s = nullptr; 
  s = parse_if_declaration_statement();
  if(!s) s = parse_if_while_statement();  
  if(!s) s = parse_if_if_statement();
  if(!s) s = parse_if_assignment_statement();  
  // last
  if(!s) s = parse_if_expression_statement();   
  return s; 

  /*
  if(parse_if_return_statement()) return true;
  else if(parse_if_continue_statement()) return true;
  else if(parse_if_break_statement()) return true;
  else if(parse_if_while_statement()) return true;
  else if(parse_if_if_statement()) return true; 
  else if(parse_if_block_statement()) return true;
  else if(parse_if_expression_statement()) return true; 
  else if(parse_if_declaration_statement()) return true;
  return false; 
  */
}
/*

bool parser::parse_if_return_statement()
{
  if(current_tok.name == kw_return)
  {
    match(kw_return);
    try{ parse_expression(); }
    catch(...) { ;}
    match(tok_semicolon);
    return true; 
  }
  return false; 
}

bool parser::parse_if_continue_statement()
{
  // lex continue
  return false;  
}

bool parser::parse_if_break_statement()
{
  // lex break
  return false; 
}
*/
stmt* parser::parse_if_while_statement()
{
  if(match_if(kw_while))
  {
    match(tok_left_paren);
    expr* cond = parse_expression();
    match(tok_right_paren); 
    stmt* body = parse_if_block_statement();
    return new while_stmt(cond, body); 
  }
  return nullptr; 
}

stmt* parser::parse_if_if_statement()
{
  if(current_tok.name == kw_if)
  {
    match(kw_if);
    match(tok_left_paren);
    expr* cond = parse_expression(); 
    match(tok_right_paren);
    stmt* body = parse_if_block_statement(); 
    stmt* else_body = nullptr; 
    if(match_if(kw_else)) 
      else_body = parse_if_block_statement();
    stmt* s = act.on_if_statement(cond, body, else_body);  
    return s; 
  }
  return nullptr; 
}

/*
bool parser::parse_if_statement_seq()
{
  if(parse_if_statement())
  {
    while(parse_if_statement());
    return true;  
  }
  return false; 
}
*/
stmt* parser::parse_if_block_statement()
{
  if(match_if(tok_left_brace))
  {
    stmt_list stmts; 
    while(current_tok.name != tok_right_brace)
    {
      stmt* s = parse_if_statement(); 
      stmts.emplace_back(s);
    }
    match(tok_right_brace);
    return act.on_block_statement(stmts);
  }
  return nullptr; 
}


stmt* parser::parse_if_expression_statement()
{
  expr* e = parse_expression();   
  match(tok_semicolon);
  
  return act.on_expression_statement(e); 
}
  
stmt* parser::parse_if_declaration_statement()
{
  decl* d =  parse_variable_definition();  
  if(d)
  { 
    return act.on_declaration_statement(d);
  }
  return nullptr; 
}

stmt* parser::parse_if_assignment_statement()
{
  if(current_tok.name == tok_identifier)
  {
    symbol s = current_tok.attribute.sym;
    accept();  
    match(tok_assignment_operator);
    expr * e = parse_expression();
    match(tok_semicolon); 
    return act.on_assignment_statement(s, e);
  }
  return nullptr; 
}
/*
//declarations

void parser::parse_parameter()
{
  match(tok_identifier); 
  match(tok_colon);
  parse_type(); 
}

void parser::parse_parameter_list()
{
  parse_parameter(); 
  while(match_if(tok_comma)) parse_parameter(); 
}

decl* parser::parse_function_definition()
{
  match(kw_def);
  match(tok_identifier);
  match(tok_left_paren);
  try { parse_parameter_list(); }
  catch(...) { ; }
  match(tok_right_paren);
  match(tok_arrow);
  parse_type();
  if(!parse_if_block_statement())
    throw std::runtime_error("Expected block statement.");
}

void parser::parse_constant_definition()
{
  match(kw_let);
  match(tok_identifier);
  match(tok_colon);
  parse_type(); 
  match(tok_assignment_operator);
  parse_expression(); 
  match(tok_semicolon);
}
*/

decl* parser::parse_variable_definition()
{
  expr* e = nullptr; 
  if(match_if(kw_var))
  {
  token tok = match(tok_identifier);
  symbol sym = tok.attribute.sym; 
  match(tok_colon);
  type* t = parse_basic_type();
  accept();  
  //parse_type();
  if(match_if(tok_assignment_operator))
    e = parse_additive_expression(); 
  match(tok_semicolon);
  return act.on_value_decl(sym, t, e);
  }
  return nullptr; 
  //decl* d = new decl(decl::is_false_kind);
  //return d; 
}


decl* parser::parse_parameter()
{
  if(current_tok.name == tok_identifier)
  {
    symbol s = current_tok.attribute.sym;
    accept(); 
    match(tok_colon);
    type * t = parse_basic_type(); 
    return act.on_parm_decl(s, t);  
  }
  
}

decl_list parser::parse_parameter_list()
{
  decl_list decls; 
  decl* d = parse_parameter();
  if(d) decls.emplace_back(d);
  while(match_if(tok_comma)) 
  {
    d = parse_parameter(); 
    decls.emplace_back(d);
  }
  return decls; 
}

/*
void parser::parse_local_declaration()
{
  parse_object_definition();
}

void parser::parse_declaration()
{
  bool success = true; 
  try { parse_function_definition(); }
  catch(std::runtime_error e) { success = false; }
  if(!success) 
  {
    success = true; 
    try { parse_local_declaration(); }
    catch(std::runtime_error e) { success = false; }  
  }
  if(!success)
    throw std::runtime_error("Expected declaration.");
}

void parser::parse_declaration_seq()
{
  while(current_tok.name != tok_end_of_file)
  { parse_declaration(); }
}

void parser::parse_program()
{
  parse_declaration_seq(); 
}
*/

