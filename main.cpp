#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"
#include "codegen.hpp"

int main(int argc, char* argv[])
{
  symbol_table syms;  
  std::fstream ifs(argv[1]);
  if(!ifs) throw std::runtime_error("Couldn't open file"); 
  std::string file, line; 
  while(!ifs.eof())
  {
    getline(ifs, line);
    line += '\n';
    file.append(line);
  }

  parser p(syms, file);
  stmt_list s = p.parse(); 
  generate(s);
}
