#pragma once
#include <vector>

struct type 
{
  enum kind {
    bool_kind, 
    char_kind, 
    int_kind,
    float_kind,
    ptr_kind, 
    ref_kind,
    fn_kind, 
  };
 
  kind k; 

  type(kind kind_) : k(kind_)
    { }
};

using type_list = std::vector<type*>;

struct bool_type : type 
{
  bool_type() : type(bool_kind)
    { }
};

struct char_type : type
{
  char_type() : type(char_kind)
    { }
};

struct int_type : type 
{
  int_type() : type(int_kind)
    { }
};

struct float_type : type
{
  float_type() : type(float_kind)
   { }
};
/*
struct ptr_type : type
{
  ptr_type(type* t) : type(ptr_kind), elem(t)
    { }

  type* elem;  
};

strut ref_type : type
{
  ref_type(type* t) : type(ref_kind), elem(t)
    { }

  type* elem; 
};

struct fn_type : type
{
  fn_type(type_list& parms_, type* t) : type(fn_kind), parms(parms_), elem(t)
    { }

  type* elem; 
  type_list parms; 
};
*/

