#ifndef OBJECT_FACTORY
#define OBJECT_FACTORY

#include"../Lexer/Lexer.hpp"
#include"../SchemeObjects/Object.hpp"

class ObjectFactory{
public:
  static Object* getSelfEvaluatingObj(Lexer& lex);
  static Object* getIntegerObj(Lexer& lex);
  static Object* getStringObj(Lexer& lex);
  static Object* getSymbolObj(Lexer& lex);
  static Object* getListObj(Lexer& lex);
  static Object* getQuoteObj(Lexer& lex);
  static Object* getCharObj(Lexer& lex);
  //static Object* getVectorObj(Lexer& lex);
  static Object* getBoolObj(Lexer& lex);
  static Object* getSharpObj(Lexer& lex);
};

#endif
