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

  llvm::Value* generate_expr(expr* e);
  llvm::Value* generate_int_expr(int_expr* e);

  void generate_declaration_statement(decl_stmt* s); 

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
  default: 
     throw std::logic_error("invalid type.");
  }
}

llvm::Type* cg::get_int_type(int_type* t)
{
  return llvm::Type::getInt32Ty(*ll);
}

llvm::Value* cg::generate_expr(expr* e)
{
  switch(e->k)
  {
  case expr::int_kind: 
    return generate_int_expr(static_cast<int_expr*>(e));
  default: 
    throw std::runtime_error("invalid expression");
  }
}

llvm::Value* cg::generate_int_expr(int_expr* e)
{
  return llvm::ConstantInt::get(get_type(e->t), e->val, true);
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

void cg::generate()
{
  for(std::vector<stmt*>::iterator it = stmts->begin(); it != stmts->end(); ++it)
  {
    switch((*it)->k)
    {
    case stmt::decl_kind: 
      generate_declaration_statement(static_cast<decl_stmt*>(*it));
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
