#pragma once 
#include <unordered_set>
using symbol = const std::string*; 

class symbol_table 
{
  private:
  std::unordered_set<std::string> syms; 
  
  public: 
  symbol get(const std::string& str)
    { return &*syms.insert(str).first; }
};
