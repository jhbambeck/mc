#pragma once
#include <vector>
//#include "statement.hpp"
#include "decl.hpp"
#include "type.hpp"

struct expr
{
  enum kind
  {
    bool_kind, 
    int_kind, 
    float_kind, 
    id_kind, 
    unop_kind, 
    binop_kind, 
    ptr_kind, 
    call_kind, 
    index_kind, 
    cast_kind, 
    assign_kind,
    cond_kind, 
    conv_kind,
    is_false_kind,
  };

  expr(kind ki, type* ty) : k(ki), t(ty)
    { }

  expr(kind ki) : k(ki), t()
   { }

  expr() 
    { }

  operator bool() const { return k != is_false_kind; }

  kind k; 
  type* t;   
};

using expr_list = std::vector<expr*>;

struct bool_expr : expr
{
  bool_expr(type* t, bool b) : expr(bool_kind, t), val(b)
    { }

  bool val;
};

struct int_expr : expr
{
  int_expr(type* t, int n) : expr(int_kind, t), val(n)
    { }

  int val; 
};

struct float_expr : expr
{
  float_expr(type* t, double n) : expr(float_kind, t), val(n)
    { }

  double val;
};

struct id_expr : expr
{
  id_expr(type* t, decl* d) : expr(id_kind, t), ref(d)
    { }

  decl* ref; 
};
/*
enum unop
{ 
  unop_cmp, 
  unop_not,
  unop_addr, 
  unop_dref,
};

struct unop_expr : expr
{
  unop_expr(unop uo, expr* e) : expr(unop_kind), op(uo), arg(e)
    { }

  unop op; 
  expr* arg; 
};
*/

enum binop
{
  binop_add, 
  binop_sub, 
  binop_mul,
  binop_div, 
  binop_rem, 
  binop_and, 
  binop_or, 
  binop_xor, 
  binop_shl, 
  binop_shr, 
  binop_land, 
  binop_lor, 
  binop_eq, 
  binop_ne, 
  binop_lt, 
  binop_gt, 
  binop_le, 
  binop_ge,
  binop_, 
};

struct binop_expr : expr 
{
  binop_expr(type* t, binop bo, expr* e1, expr* e2)
    : expr(binop_kind, t), op(bo), lhs(e1), rhs(e2)
    { }
  
  binop op; 
  expr* lhs; 
  expr* rhs; 
};
/*
struct postfix_expr : expr
{
  postfix_expr(kind k, type* t, expr* e,  expr_list& a)
    : expr(k), base(e), args(a)
    { }

  expr* base; 
  expr_list args; 
};

struct call_expr : postfix_expr
{
  call_expr(type* t, expr* e, expr_list& a)
    : postfix_expr(call_kind, t, e, a)
    { }
};

struct index_expr : postfix_expr
{
  index_expr(type* t, expr* e, expr_list& a)
    : postfix_expr(index_kind, t, e, a)
    { }
};

struct cast_expr : expr
{
  cast_expr(expr* e, type* t)
    : expr(cast_kind, t), src(e), dest(t)
    { }

  expr* src; 
  type* dest; 
};

struct assign_expr : expr
{
  assign_expr(type* t, expr* e1, expr* e2)
    : expr(assign_kind), lhs(e1), rhs(e2)
    { }
  
  expr* lhs; 
  expr* rhs; 
};

struct cond_expr : expr
{
  cond_expr(type* t, expr* e1, expr* e2, expr* e3)
    : expr(cond_kind, t), cond(e1), t(e2), f(e3)
    { }

  expr* cond; 
  expr* t; 
  expr* f; 
};

enum conversion
{
  conv_identity, // no conversion
  conv_value, // conversion to value
  conv_bool, //conversion from T to bool
  conv_char, // conversion from int to char
  conv_int, // conversion from T to int
  conv_ext, // conversion from int to float
  conv_trunc, //conversion from float to int
};

struct conv_expr : expr
{
  conv_expr(expr* e, conversion c, type* t)
    : expr(conv_kind, t) : src(e), conv(c)
  { }

  expr* src; 
};

*/
