#include "lexer.hpp"

char lexer::peek(int i)
{
  first += i; 
  char ch = *first; 
  first -= i; 
  return ch; 
}

char lexer::accept()
{
  char c = *first; 
  ++first; 
  return c; 
}

void lexer::ignore()
{ 
  ++first;
}

bool lexer::isstringchar(char c, bool secondescape)
{
  if(secondescape)
  {
    switch(c)
    {
      case '\'':
      case '"':
      case '\\':
      case 'a':
      case 'b': 
      case 'f':
      case 'n':
      case 'r': 
      case 't': 
      case 'v':
      return true; 
    }
  }
  else 
  {
    if(isalpha(c) || isdigit(c)) return true; 
    switch(c)
    {
      case '_':
      case '{':
      case '}':
      case '[':
      case ']':
      case '(':
      case ')':
      case '<':
      case '>':
      case '#':
      case '%':
      case ':':
      case ';':
      case '?':
      case '*': 
      case '+':
      case '-':
      case '/':
      case '^':
      case '&':
      case '|':
      case '~':
      case '!':
      case '=':
      case ',':
      case '\\':
        return true; 
    }
  }
  return false; 
}

bool lexer::iskeyword(std::string& lexeme)
{
  if(lexeme == "and" ||
     lexeme == "bool" ||
     lexeme == "char" ||
     lexeme == "def" ||
     lexeme == "else" ||
     lexeme == "false" ||
     lexeme == "float" ||
     lexeme == "if" ||
     lexeme == "int" ||
     lexeme == "let" ||
     lexeme == "not" ||
     lexeme == "or" || 
     lexeme == "true" ||
     lexeme == "var" ||
     lexeme == "as" ||
     lexeme == "return" ||
     lexeme == "void" ||
     lexeme == "while" ||
     lexeme == "const" ||
     lexeme == "volatile" ||
     lexeme == "continue" ||
     lexeme == "break"
    ) return true; 
    return false; 
}

bool lexer::isbinarydigit(char c)
{
  if(c == '0' || c == '1') return true; 
  return false; 
}

bool lexer::ishexdigit(char c)
{
  if(isdigit(c)) return true; 
  switch(c)
  {
    case 'a':
    case 'b': 
    case 'c': 
    case 'd': 
    case 'e':
    case 'f': 
    case 'A': 
    case 'B': 
    case 'C': 
    case 'D': 
    case 'E': 
    case 'F':
      return true;  
  }
  return false; 
} 

bool lexer::isnondigit(char c)
{
  if(isalpha(c) || c == '_') return true; 
  else return false; 
}

token lexer::lex_string() 
{
  assert(*first == '"');
  ++first;
  bool secondescape = false;  
  while(*first != '"')
  {
    assert(isstringchar(*first, secondescape));
    if(*first == '\\' && secondescape == false) 
      secondescape = true; 
    else secondescape = false; 
    ++first; 
  }
  assert(secondescape == false);
  int stringlen = first - token_loc;
  first = token_loc + 1;
  char* str = new char[stringlen];
  for(int i = 0; i < stringlen - 1; i++)
  {
    str[i] = *first; 
    ++first; 
  } 
  ++first; 
  str[stringlen - 1] = '\0';
  
  token tok; 
  tok.name = tok_string_literal; 
  tok.attribute.stringval = str; 
  return tok; 
}

token lexer::lex_rel_assign_operator()
{
  char c;
  token tok; 
  tok.name = tok_relational_operator;  
  switch(*first)
  {
    case '<':
      c = peek(1);
      if(c == '=') 
      {
        first += 2; 
        tok.attribute.rel_op= less_than_or_equal_to;  
        return tok; 
      }
      else 
      {  
        ++first; 
        tok.attribute.rel_op = less_than; 
        return tok;
      }
      break; 
    case '>':
      c = peek(1);
      if(c == '=')
      {
        first += 2;
        tok.attribute.rel_op = greater_than_or_equal_to;   
        return tok;
      }
      else 
      {
        ++first; 
        tok.attribute.rel_op = greater_than; 
        return tok;
      }
      break; 
    case '=':
      c = peek(1);
      if(c == '=')
      {
        first += 2; 
        tok.attribute.rel_op = equal; 
        return tok;
      } 
      else 
      {
        ++first; 
        tok.name = tok_assignment_operator; 
        return tok;  
      }
      break; 
  }
}

token lexer::lex_arithmetic_operator()
{
  token tok; 
  tok.name = tok_arithmetic_operator; 
  switch(*first)
  { 
    case '*':  
      ++first; 
      tok.attribute.arith_op = multiply;  
      return tok; 
    case '+': 
      ++first;
      tok.attribute.arith_op = add; 
      return tok; 
    case '/': 
      ++first; 
      tok.attribute.arith_op = divide; 
      return tok; 
    case '-':
      if(peek(1) == '>')
      {
        first += 2; 
        tok.name = tok_arrow; 
        return tok; 
      }
      ++first; 
      tok.attribute.arith_op = subtract; 
      return tok; 
    case '%': 
      ++first; 
      tok.attribute.arith_op = modulo;
      return tok;
  }
} 

token lexer::lex_bitwise_operator()
{
  token tok;
  tok.name = tok_bitwise_operator; 
  switch(*first)
  {
    case '&':
      ++first; 
      tok.attribute.bit_op = bitwise_and; 
      return tok;
    case '|':
      ++first; 
      tok.attribute.bit_op = bitwise_or; 
      return tok; 
    case '~':
      ++first;
      tok.attribute.bit_op = bitwise_complement; 
      return tok; 
    case '^':  
      ++first; 
      tok.attribute.bit_op = bitwise_xor; 
      return tok;
    case '!':
      ++first; 
      tok.attribute.bit_op = bitwise_not; 
      return tok;  
  }
}

token lexer::lex_conditional_operator() 
{
  if(*first == '?')
  {
    ++first; 
    token tok; 
    tok.name = tok_conditional_operator;
    return tok; 
  }
}

token lexer::lex_punctuator()
{
  token tok; 
  switch(*first)
  {
    case '{':
      ++first; 
      tok.name = tok_left_brace; 
      return tok;  
    case '}': 
      ++first; 
      tok.name = tok_right_brace; 
      return tok; 
    case '(': 
      ++first; 
      tok.name = tok_left_paren; 
      return tok; 
    case ')':
      ++first;   
      tok.name = tok_right_paren;
      return tok;  
    case '[': 
      ++first; 
      tok.name = tok_left_bracket; 
      return tok; 
    case ']': 
      ++first;
      tok.name = tok_right_bracket; 
      return tok; 
    case ',': 
      ++first; 
      tok.name = tok_comma; 
      return tok; 
    case ';': 
      ++first; 
      tok.name = tok_semicolon; 
      return tok; 
    case ':': 
      ++first; 
      tok.name = tok_colon; 
      return tok; 
  }
}

token lexer::lex_decimal()
{
  std::string dec_string; 
  while(isdigit(*first))
  {
    dec_string += *first; 
    ++first; 
  }
  if(*first == '.')
  {
    if(!isdigit(peek(1)))
      throw std::runtime_error("expected floating-point fraction");
    first = token_loc; 
    return lex_floating_point();  
  }
  int val = std::stoi(dec_string, 0, 10);
  token tok; 
  tok.name = tok_decimal_integer_literal; 
  tok.attribute.intval = val;
  return tok; 
}

token lexer::lex_floating_point()
{
  assert(isdigit(*first));
  char* intgr;
  char* fract; 
  char* exp; 
  
  //int
  while(isdigit(*first))
    ++first; 
  assert(*first == '.');
  int sz = first - token_loc + 1; 
  intgr = new char[sz];
  first = token_loc; 
  for(int i = 0; i < sz - 1; i++)
  {
    intgr[i] = *first; 
    ++first; 
  }
  intgr[sz - 1] = '\0';
  ++first; 

  //fraction
  assert(isdigit(*first));
  const char* temp_loc = first; 
  while(isdigit(*first)) 
  {
    ++first; 
  }
  sz = first - temp_loc + 1; 
  fract = new char[sz];
  first = temp_loc; 
  for(int i = 0; i < sz - 1; i++)
  {
    fract[i] = *first; 
    ++first; 
  }
  fract[sz-1] = '\0'; 

  //exponent
  bool neg = false; 
  if(*first != 'e' && *first != 'E')
  {
    exp = new char[2];
    exp[0] = '0';
    exp[1] = '\0';
  }
  else
  {
    ++first; 
    temp_loc = first;
    if(*first == '-')
    {
      neg = true; 
      ++first; 
    }
    else if(*first == '+')
    {
      ++first;  
    }
    assert(isdigit(*first)); 
    temp_loc = first; 
    while(isdigit(*first))
    {
      ++first; 
    }
    sz = first - temp_loc + 1;
    exp = new char[sz];
    first = temp_loc;
    for(int i = 0; i < sz - 1; i++)
    {
      exp[i] = *first;
      ++first;  
    } 
    exp[sz - 1] = '\0';
  }
  
  //math
  int i = atoi(intgr);
  int e = atoi(exp);
  if(neg) e *= -1; 
  double f = 0;
  double f_e = .1; //fractional exponent to sum fract
  int k = 0; //iterate over fract
  char* temp = new char[2];
  temp[1] = '\0';
  while(fract[k] != '\0')
  {
    temp[0] = fract[k];
    f += f_e * atoi(temp);
    f_e *= .1; 
    ++k; 
  }
  double value = (i + f) * pow(10, e);
  token tok; 
  tok.name = tok_floating_point_literal; 
  tok.attribute.doubleval = value; 
  return tok;   
}

token lexer::lex_binary()
{
  first += 2;
  std::string bin_string;  
  while(isbinarydigit(*first))
  {
    bin_string += *first;
    ++first;  
  }  
  int val = std::stoi(bin_string, 0, 2);
  token tok; 
  tok.name = tok_binary_integer_literal;   
  tok.attribute.intval = val; 
  return tok; 
}

token lexer::lex_hexadecimal()
{
  first += 2; 
  std::string hex_string; 
  while(ishexdigit(*first))
  {
    hex_string += *first; 
    ++first; 
  }
  int val = std::stoi(hex_string, 0, 16);
  token tok; 
  tok.name = tok_hexadecimal_integer_literal; 
  tok.attribute.intval = val; 
  return tok; 
}

token lexer::lex_number()
{
  if(*first == '0')
  {
    if(peek(1) == 'x' || peek(1) == 'X')
      return lex_hexadecimal(); 
    else if(peek(1) == 'b' || peek(1) == 'B')
      return lex_binary();
    else if(isdigit(peek(1)))
      return lex_decimal();  
  } 
  else if(isdigit(*first))
    return lex_decimal(); 
}

token lexer::lex_identifier(std::string& lexeme)
{
  token tok;
  tok.name = tok_identifier; 
  tok.attribute.sym = syms->get(lexeme);
  return tok; 
}

token lexer::lex_keyword(std::string& lexeme)
{
  token tok; 
  if(lexeme == "and") tok.name = kw_and; 
  if(lexeme == "bool") tok.name = kw_bool; 
  if(lexeme == "char") tok.name = kw_char; 
  if(lexeme == "def") tok.name = kw_def; 
  if(lexeme == "else") tok.name = kw_else; 
  if(lexeme == "false") tok.name = kw_false; 
  if(lexeme == "float") tok.name = kw_float; 
  if(lexeme == "if") tok.name = kw_if; 
  if(lexeme == "int") tok.name = kw_int; 
  if(lexeme == "let") tok.name = kw_let; 
  if(lexeme == "not") tok.name = kw_not; 
  if(lexeme == "or") tok.name = kw_or; 
  if(lexeme == "true") tok.name = kw_true; 
  if(lexeme == "var") tok.name = kw_var;
  if(lexeme == "as") tok.name = kw_as; ;
  if(lexeme == "return") tok.name = kw_return;
  if(lexeme == "void") tok.name = kw_void; 
  if(lexeme == "while") tok.name = kw_while; 
  if(lexeme == "const") tok.name = kw_const; 
  if(lexeme == "volatile") tok.name = kw_volatile; 
  if(lexeme == "break") tok.name = kw_break; 
  if(lexeme == "continue") tok.name = kw_continue; 
  return tok;  
}

token lexer::lex_identifier_keyword() 
{
  std::string lexeme; 
  while(isdigit(*first) || isnondigit(*first))
  {
    lexeme += *first; 
    ++first; 
  }
  if(iskeyword(lexeme)) return lex_keyword(lexeme);
  else return lex_identifier(lexeme);
}

void lexer::lex_comment()
{
  assert(*first == '#');
  while(*first != '\n') ++first; 
}

token lexer::lex() 
{
  while(!eof())
  {
  token_loc = first; 
  switch(*first)
  {
    case '<':
    case '=':
    case '>':
      return lex_rel_assign_operator(); 
      break;
    case '+':
    case '-': 
    case '/': 
    case '*':
    case '%': 
      return lex_arithmetic_operator();//lex arrow from here for now
    case '&':
    case '|': 
    case '~': 
    case '^':
    case '!':  
      return lex_bitwise_operator();
    case '?':
      return lex_conditional_operator();
    case '{': 
    case '}': 
    case '(': 
    case ')': 
    case '[': 
    case ']': 
    case ',': 
    case ';': 
    case ':':
      return lex_punctuator(); 
    case '0': 
    case '1': 
    case '2': 
    case '3': 
    case '4': 
    case '5': 
    case '6': 
    case '7': 
    case '8': 
    case '9':
      return lex_number();  
    case '"': 
      return lex_string();
    case '#':
      lex_comment();
      break;        
    case ' ': 
    case '\n':
    case '\r': 
    case '\t':
      ++first;  
      break;  
  } 
  if(isnondigit(*first)) return lex_identifier_keyword(); 
  }
  token tok;
  tok.name = tok_end_of_file; 
  return tok;  
}
