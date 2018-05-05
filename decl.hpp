#pragma once
#include "token.hpp"
#include "expr.hpp"
#include "type.hpp"
#include <vector>

class type; 
class expr; 
class decl;

struct decl
{
  enum kind 
  {
    prog_kind, 
    var_kind, 
    const_kind, 
    value_kind, 
    parm_kind, 
    fn_kind,
    is_false_kind, 
  };

  decl(kind ki, symbol sym) : k(ki), name(sym)
    { }

  decl(kind ki) : k(ki)
    { }

  operator bool() const {return k != is_false_kind;}

  kind k; 
  symbol name;  
};

using decl_list = std::vector<decl*>;
/*
struct prog_decl : decl
{
  prog_decl(decl_list& dl) : decl(prog_kind, nullptr), decls(dl)
    { }

  decl_list decls; 
};
*/
struct type_decl : decl
{
  type_decl(kind k, symbol sym, type* ty) : decl(k, sym), t(ty)
    { }

  type* t; 
};

struct object_decl : type_decl
{
  object_decl(kind k, symbol sym, type* t, expr* e)
    : type_decl(k, sym, t), init(e)
    { }

  expr* init; 
};

struct value_decl : object_decl
{
  value_decl(symbol sym, type* t, expr* e = nullptr)
    : object_decl(value_kind, sym, t, e)
    { }
};


struct parm_decl : object_decl
{
  parm_decl(symbol sym, type* t) : object_decl(parm_kind, sym, t, nullptr)
   { }
};

/*
struct fn_decl : type_decl
{
  fn_decl(symbol sym, type* t, decl_list& p, stmt* s = nullptr)
    : type_decl(fn_kind, sym, t), parms(p), body(s)
    { }

  decl_list parms; 
  stmt* body; 
};
*/
