#include"ObjectFactory.hpp"
#include"../Parser/Parser.hpp"
#include"../SchemeObjects/SelfEvalObjects/NumberObjects/IntegerObj.hpp"
#include"../SchemeObjects/SelfEvalObjects/StringObj.hpp"
#include"../SchemeObjects/SymbolObj.hpp"
#include"../SchemeObjects/ListObj.hpp"
#include"../SchemeObjects/CharObj.hpp"
#include"../SchemeObjects/BoolObj.hpp"
#include"../SchemeObjects/QuoteObj.hpp"


void checkFileEnd(Lexer& lex){
  if(lex.isEnd())
    throw std::string("The file ends in the middle.");
}

Word* getWord(Token* t){;
  Word* word = (Word*)t;
  return word;
}

bool isEqualName(std::string name, Token* token){
  if(token->getType() == WORD){
    Word* word = getWord(token);
    return word->getName() == name;
  }
  return false;
}

Object* ObjectFactory::getSelfEvaluatingObj(Lexer& lex){
  Object* obj = NULL;
  if(lex.getToken()->getType() == NUM){
    obj = getIntegerObj(lex);
  }else if(lex.getToken()->getType() == STRING){
    obj = getStringObj(lex);
  }
  return obj;
}

Object* ObjectFactory::getIntegerObj(Lexer& lex){
  Num* n = dynamic_cast<Num*>(lex.getToken());
  int num = n->getVal();
  IntegerObj* obj = new IntegerObj(num);
  obj->setStart(n->getStartRow(), n->getStartColmn());
  obj->setEnd(n->getEndRow(), n->getEndColmn());
  return obj;
}

Object* ObjectFactory::getStringObj(Lexer& lex){
  ScString* token_str = dynamic_cast<ScString*>(lex.getToken());
  StringObj* obj = new StringObj(token_str->getString());
  obj->setStart(token_str->getStartRow(), token_str->getStartColmn());
  obj->setEnd(token_str->getEndRow(), token_str->getEndColmn());
  return obj;
}

Object* ObjectFactory::getSymbolObj(Lexer& lex){
  Word* w = dynamic_cast<Word*>(lex.getToken());
  SymbolObj* obj = new SymbolObj(w->getName());
  obj->setStart(w->getStartRow(), w->getStartColmn());
  obj->setEnd(w->getEndRow(), w->getEndColmn());
  return obj;
}

Object* ObjectFactory::getQuoteObj(Lexer& lex){
  Token* start_t = lex.getToken();
  lex.next();
  if(lex.isEnd() || lex.getToken()->getType() == RIGHT_PARAM)
    throw std::string("Empty statement in next quote`");
  Object* obj = Parser::getSyntaxTree(lex);
  QuoteObj* quote_obj = new QuoteObj(obj);
  quote_obj->setStart(start_t->getStartRow(), start_t->getStartColmn());
  quote_obj->setEnd(lex.getToken()->getEndRow(), lex.getToken()->getEndColmn());
  return quote_obj;
}

Object* ObjectFactory::getListObj(Lexer& lex){
  ListObj* list_obj = new ListObj();
  Token* start_t = lex.getToken();
  list_obj->setStart(start_t->getStartRow(), start_t->getStartColmn());
 
  int cnt = 0;
  lex.next();
  try{
    while(!lex.isEnd() && lex.getToken()->getType() != RIGHT_PARAM){
      ++cnt;
      // リストの各要素を構文解析して取得し、追加
      Object* obj = Parser::getSyntaxTree(lex);
      list_obj->add(obj);
    }
  }catch(std::string& s){
    delete list_obj;
    throw s;
  }
  
  if(lex.isEnd()){
    // リストの途中で、ファイルが終わっている場合
    delete list_obj;
    throw std::string("Unclosed parenthes");
  }

  Token* end_t = lex.getToken();
  
  if(cnt == 0){
    // リストが空の時は、空のペアーオブジェクトを返す
    delete list_obj;
    PairObj* pair_obj =  new PairObj();
    pair_obj->setStart(start_t->getStartRow(), start_t->getStartColmn());
    pair_obj->setEnd(end_t->getEndRow(), end_t->getEndColmn());
    return pair_obj;
  }
  list_obj->setEnd(end_t->getEndRow(), end_t->getEndColmn());
  return list_obj;
}

bool isBehind(Token* lhs, Token* rhs){
  return
    (lhs->getEndRow() == rhs->getStartRow()) &&
    (lhs->getEndColmn() == rhs->getStartColmn());
}

char getChar(std::string str){
  if(str == "newline")
    return '\n';
  else if(str == "space")
    return ' ';
  if(str.length() != 1)
    throw std::string("after (#\\) it must be a letter");
  return str[0];
}

Object* ObjectFactory::getCharObj(Lexer& lex){
  lex.next();
  Token* back_slash_token = lex.getToken();
  Token* next_token = lex.getNextToken();
  
  if(next_token == NULL)
    throw std::string("The file ends in the middle.");
  
  CharObj* obj = NULL;
  if(!isBehind(back_slash_token, next_token)){
    // スラッシュのすぐ後ろにトークンがない場合、スペースがあるのでスペースの文字
    obj = new CharObj(' ');
  }else{
    std::string str = next_token->getCode();
    char c = getChar(str);
    obj = new CharObj(c);
    lex.next();
  }
  return obj;
}          

bool getBoolValue(Token* t){
  std::string code = t->getCode();
  if(code.length() > 1){
    throw std::string("Sharp syntax error");
  }
  if(code == "t")
    return true;
  else if(code == "f")
    return false;
  else
    throw std::string("Sharp syntax error");
  return false;
}

Object*  ObjectFactory::getBoolObj(Lexer& lex){
  lex.next();  
  bool bool_value = getBoolValue(lex.getToken());
  return new BoolObj(bool_value);
}

Object*  ObjectFactory::getSharpObj(Lexer& lex){
  Token* sharp_token = lex.getToken();
  Token* next_token = lex.getNextToken();

  if(next_token == NULL)
    throw std::string("Sharp syntax error");

 
  if(!isBehind(sharp_token, next_token))
    throw std::string("Sharp syntax error");

 
  if(next_token->getType() == LEFT_PARAM){
    //ベクター
    //return getVectorObj(l);
  }else if(next_token->getType() == BACK_SLASH){
    return getCharObj(lex);
  }else if(next_token->getType() == WORD){
    return getBoolObj(lex);
  }else{
    throw std::string("Sharp expression syntax error");
  }
  return NULL;
}
