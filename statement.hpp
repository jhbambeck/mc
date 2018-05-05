#include "expr.hpp"
#include "decl.hpp"
#include "expr.hpp"
#include <vector>

struct stmt
{
  enum kind 
  {
    block_kind,
    when_kind, 
    if_kind, 
    while_kind, 
    break_kind, 
    cont_kind, 
    ret_kind,
    decl_kind, 
    expr_kind,
    assign_kind,
    is_false_kind, 
  };
 
  stmt(kind ki) : k(ki)
    { }
  
  operator bool() const {return k != is_false_kind;}

  kind k;
};

using stmt_list = std::vector<stmt*>;

struct block_stmt : stmt
{
  block_stmt(stmt_list& sl) : stmt(block_kind), stmts(sl)
    { }

  stmt_list stmts; 
};

struct when_stmt : stmt 
{
  when_stmt(expr* c, stmt* s1) : 
    stmt(when_kind), cond(c), body(s1)
    { }

  expr* cond; 
  stmt* body; 
};

struct if_stmt : stmt 
{
  if_stmt(expr* c, stmt* s1, stmt* s2)
    : stmt(if_kind), cond(c), true_e(s1), false_e(s2)
    { }

  expr* cond; 
  stmt* true_e; 
  stmt* false_e; 
};

struct while_stmt : stmt
{
  while_stmt(expr* c, stmt* s)
    : stmt(while_kind), cond(c), body(s) 
    { }

  expr* cond; 
  stmt* body; 
};

struct break_stmt : stmt
{
  break_stmt() : stmt(break_kind)
    { }
};

struct cont_stmt : stmt
{
  cont_stmt() : stmt(cont_kind)
    { }
};

struct ret_stmt : stmt
{
  ret_stmt(expr* e) : stmt(ret_kind), val(e)
    { }

  expr* val; 
};

struct decl_stmt : stmt
{
  decl_stmt(decl* de) : stmt(decl_kind), d(de)
    { }
 
  decl* d; 
};

struct expr_stmt : stmt
{
  expr_stmt(expr* ex) : stmt(expr_kind), e(ex)
    { }

  expr* e; 
};

struct  assign_stmt : stmt
{
  assign_stmt(symbol s, expr* e) : stmt(assign_kind), val(e), name(s)
   { }
   
  symbol name; 
  expr* val; 
}; 

