#ifndef SCHEME_PARSER
#define SCHEME_PARSER

#include"../SchemeObjects/Object.hpp"
#include"../Lexer/Lexer.hpp"

class Parser{
public:
  // リストと自己評価式、シャープ式、シンボルを構文解析し、構文解析木を返す
  static Object* getSyntaxTree(Lexer& l);
};

#endif
