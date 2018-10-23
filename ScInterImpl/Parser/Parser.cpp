#include"parser.hpp"
#include"../Lexer/Tokens.hpp"
#include"../ObjectFactory/ObjectFactory.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<cassert>

bool isSelfEvaluating(Token* token){
  return(token->getType() == STRING) ||
    (token->getType() == NUM);
}

bool isSymbol(Token* token){
  return token->getType() == WORD;
}

bool isQuote(Token* token){
  return token->getType() == QUOTE;
}

bool isSharpObj(Token* token){
  return token->getType() == SHARP;
}

Object* Parser::getSyntaxTree(Lexer& l){
  Object* obj = NULL;
  if(!l.isEnd()){
    Token* token = l.getToken();
    if(isSelfEvaluating(token)){
      obj = ObjectFactory::getSelfEvaluatingObj(l);
      l.next();
    }else if(isQuote(token)){
      obj = ObjectFactory::getQuoteObj(l);
    }else if(isSymbol(token)){
      obj = ObjectFactory::getSymbolObj(l);
      l.next();
    }else if(token->getType() == LEFT_PARAM){
      obj = ObjectFactory::getListObj(l);
      l.next();
    }else if(token->getType() == SHARP){
      obj = ObjectFactory::getSharpObj(l);
      l.next();
    }else{
      throw std::string("undefine syntax");
    }
  }
  return obj;
}

