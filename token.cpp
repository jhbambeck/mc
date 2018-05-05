#include "token.hpp"
void print_token(token tok)
{
  switch(tok.name)
  {
    case tok_relational_operator:
      if (tok.attribute.rel_op == equal)
        std::cout << "<relational_operator: equal>"; 
      else if (tok.attribute.rel_op == less_than)
        std::cout << "<relational_operator: less_than>";
      else if (tok.attribute.rel_op ==  greater_than) 
        std::cout << "<relational_operator: greater_than>";
      else if (tok.attribute.rel_op == greater_than_or_equal_to)
          std::cout << "<relational_operator: greater_than_or_equal_to>";
      else if (tok.attribute.rel_op ==  less_than_or_equal_to) 
        std::cout << "<relational_operator: less_than_or_equal_to>";  
      break;
    case tok_assignment_operator: 
      std::cout << "<assignment_operator: >";
      break;
    case tok_arithmetic_operator: 
      if(tok.attribute.arith_op == add)
        std::cout << "<arithmetic_operator: add>";
      else if(tok.attribute.arith_op == subtract)
        std::cout << "<arithmetic_operator: subtract>";
      else if(tok.attribute.arith_op == multiply)
       std::cout << "<arithmetic_operator: multiply>"; 
      else if(tok.attribute.arith_op == divide)
        std::cout << "<arithmetic_operator: divide>";
      else if(tok.attribute.arith_op == modulo)
        std::cout << "<arithmetic_operator: modulo>";
      break;
    case tok_bitwise_operator: 
      if(tok.attribute.bit_op == bitwise_and)
        std::cout << "<bitwise_operator: bitwise_and>";
      else if(tok.attribute.bit_op == bitwise_or)
        std::cout << "<bitwise_operator: bitwise_or>";
      else if(tok.attribute.bit_op == bitwise_complement)
        std::cout << "<bitwise_operator: bitwise_complement>";
      else if(tok.attribute.bit_op == bitwise_xor)
        std::cout << "<bitwise_operator: bitwise_xor>";
      else if(tok.attribute.bit_op == bitwise_not)
        std::cout << "<bitwise_operator: bitwise_not>"; 
      break;
    case tok_conditional_operator: 
      std::cout << "<coniditional_operator: >";
      break;
    case tok_left_brace: 
      std::cout << "<left_brace: >";
      break; 
    case tok_right_brace: ;
     std::cout << "<right_brace: >";
     break; 
    case tok_left_paren: 
     std::cout << "<left_paren: >"; 
     break; 
    case tok_right_paren: 
     std::cout << "<right_paren: >";
     break; 
    case tok_left_bracket: 
     std::cout << "<left_bracket: >";
     break;
    case tok_right_bracket: 
     std::cout << "<right_bracket: >"; 
     break; 
    case tok_comma: 
     std::cout << "<comma: >";
     break; 
    case tok_semicolon: 
     std::cout << "<semicolon: >";
     break; 
    case tok_colon:
     std::cout << "<colon: >";
     break;
    case tok_hexadecimal_integer_literal: 
      std::cout << "<hexadecimal_integer_literal: 0X" 
      << std::hex << tok.attribute.intval << ">" << std::dec;
      break;
    case tok_decimal_integer_literal: 
      std::cout << "<decimal_integer_literal: "
      << tok.attribute.intval << ">";  
      break;
    case tok_binary_integer_literal: 
      std::cout << "<binary_integer_literal: 0B" 
      << inttobinstring(tok.attribute.intval) << ">";
      break;
    case tok_identifier: 
      std::cout << "<identifier: " 
      << tok.attribute.sym << ">";
      break; 
    case kw_and:
      std::cout << "<kw_and: >"; 
      break; 
    case kw_bool:
      std::cout << "<kw_bool: >"; 
      break; 
    case kw_char:
      std::cout << "<kw_char: >";
      break; 
    case kw_def:
      std::cout << "<kw_def: >";
      break; 
    case kw_else:
      std::cout << "<kw_else: >";
      break;  
    case kw_false:
      std::cout << "<kw_false: >"; 
      break; 
    case kw_float:
      std::cout << "<kw_float: >";
      break;  
    case kw_if:
      std::cout << "<kw_if: >";
      break;  
    case kw_int:
      std::cout << "<kw_int: >";
      break;  
    case kw_let:
      std::cout << "<kw_let: >";
      break;  
    case kw_not:
      std::cout << "<kw_not: >";
      break;  
    case kw_or:
      std::cout << "<kw_or: >";
      break;  
    case kw_true:
      std::cout << "<kw_true: >";
      break;  
    case kw_var:
      std::cout << "<kw_var: >";
      break;
    case kw_as:
      std::cout << "<kw_as: >";
      break; 
    case kw_return: 
      std::cout << "<kw_return: >";
      break; 
    case kw_void: 
      std::cout << "<kw_void: >";
      break;
    case kw_while: 
      std::cout << "<kw_while: >"; 
      break; 
    case tok_string_literal: 
      std::cout << "<string_literal: "
      << tok.attribute.stringval << ">";
      break;
    case tok_floating_point_literal: 
      std::cout << "<floating_point_literal: "
      << tok.attribute.doubleval << ">";
      break;
    case kw_const: 
      std::cout << "<kw_const: >";
      break; 
    case kw_volatile:
      std::cout << "<kw_volatile: >";     
      break;
    case kw_continue: 
      std::cout << "<kw_continue: >";
      break; 
    case kw_break: 
      std::cout << "<kw_break: >";
      break; 
    case tok_arrow:
      std::cout << "<arrow: >"; 
      break;  
    case tok_end_of_file: 
      std::cout << "<end_of_file: >";
      break;    
    default: 
      std::cout << "<token does not have type>";
      break; 
  }
}

std::string inttobinstring(int i)
{
  std::string binstring = std::bitset<32>(i).to_string(); 
  int p = 0; 
  while(binstring[p] == '0')
  {
    binstring.erase(p, 1);
  }
  return binstring; 
}
