#include "codegen.hpp"

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>

using variable_map = std::unordered_map<decl*, llvm::Value*>;

struct cg
{
  cg(stmt_list* s) : ll(new llvm::LLVMContext()), stmts(s)
    { mod = new llvm::Module("a.ll", *ll); }

  ~cg() { delete ll; }

  llvm::LLVMContext* get_context() { return ll; }

  std::string get_name(decl* d);
  void declare(decl* d, llvm::Value* v) 
    { globals.emplace(std::pair<decl*, llvm::Value*>(d, v)); }

  llvm::Type* get_type(type* t);
  llvm::Type* get_int_type(int_type* t);
  llvm::Type* get_bool_type(bool_type* t); 

  llvm::Value* generate_expr(expr* e);
  llvm::Value* generate_int_expr(int_expr* e);
  llvm::Value* generate_bool_expr(bool_expr* e);
  llvm::Value* generate_binop_expr(binop_expr* e);

  void generate_declaration_statement(decl_stmt* s);
  void generate_if_statement(if_stmt* s); 

  void generate(); 

  llvm::LLVMContext* ll; 
  llvm::Module* mod;
  variable_map globals; 
  stmt_list* stmts; 
};

std::string cg::get_name(decl* d)
{
  return d->get_name(); 
}

llvm::Type* cg::get_type(type* t)
{
  switch(t->k)
  {
  case type::int_kind:
    return get_int_type(static_cast<int_type*>(t));
  case type::bool_kind: 
    return get_bool_type(static_cast<bool_type*>(t));
  default: 
     throw std::logic_error("invalid type.");
  }
}

llvm::Type* cg::get_int_type(int_type* t)
{
  return llvm::Type::getInt32Ty(*ll);
}

llvm::Type* cg::get_bool_type(bool_type* t)
{
  return llvm::Type::getInt1Ty(*ll); 
}

llvm::Value* cg::generate_expr(expr* e)
{
  switch(e->k)
  {
  case expr::int_kind: 
    return generate_int_expr(static_cast<int_expr*>(e));
  case expr::bool_kind: 
    return generate_bool_expr(static_cast<bool_expr*>(e));
  case expr::binop_kind:
    return generate_binop_expr(static_cast<binop_expr*>(e));
  default: 
    throw std::runtime_error("invalid expression");
  }
}

llvm::Value* cg::generate_int_expr(int_expr* e)
{
  return llvm::ConstantInt::get(get_type(e->t), e->val, true);
}

llvm::Value* cg::generate_bool_expr(bool_expr* e)
{
  int i; 
  if(e->val) i = 1; 
  else i = 0; 
  return llvm::ConstantInt::get(get_type(e->t), i, true);
}

llvm::Value* cg::generate_binop_expr(binop_expr* e)
{
  
  llvm::Value* v1 = generate_expr(e->lhs);
  llvm::Value* v2 = generate_expr(e->rhs);
  llvm::Constant* c1 = static_cast<llvm::Constant*>(v1);
  llvm::Constant* c2 = static_cast<llvm::Constant*>(v2);
  switch(e->op)
  {
    case binop_add: 
      return llvm::ConstantExpr::getAdd(c1, c2);
    case binop_sub: 
      return llvm::ConstantExpr::getSub(c1, c2);
    case binop_mul: 
      return llvm::ConstantExpr::getMul(c1, c2);
    case binop_div: 
      return llvm::ConstantExpr::getUDiv(c1, c2);
    default:
      throw std::logic_error("Invalid binop operation.");
  }
}

void cg::generate_declaration_statement(decl_stmt* s)
{
  std::string n = get_name(s->d);
  llvm::Type* t = get_type(static_cast<value_decl*>(s->d)->t);
  llvm::Value* v = generate_expr(static_cast<object_decl*>(s->d)->init);
  llvm::Constant* c = static_cast<llvm::Constant*>(v);
  llvm::GlobalVariable* var = new llvm::GlobalVariable(*mod, t, false, 
    llvm::GlobalVariable::ExternalLinkage, c, n); 

  declare(s->d, v);
}

/*
void cg::generate_if_statement(if_stmt* s)
{
  llvm::Value* vc = generate_expr(s->cond);
  llvm::Value* vt = generate_expr(s->true_e);
  llvm::Value* vf = generate_expr(s->false_e);
  llvm::Constant* cc = static_cast<llvm::Constant*>(vc);
  llvm::Constant* ct = static_cast<llvm::Constant*>(vt);
  llvm::Constant* cf = static_cast<llvm::Constant*>(vf);
}
*/

void cg::generate()
{
  for(std::vector<stmt*>::iterator it = stmts->begin(); it != stmts->end(); ++it)
  {
    switch((*it)->k)
    {
    case stmt::decl_kind: 
      generate_declaration_statement(static_cast<decl_stmt*>(*it));
      break;
    case stmt::if_kind:
      generate_if_statement(static_cast<if_stmt*>(*it));
      break;
    default:  
      throw std::runtime_error("Bad statement kind");
    }
  }
}

void generate(stmt_list& s)
{
  cg c(&s);
  c.generate(); 
  llvm::outs() << *(c.mod);
}
