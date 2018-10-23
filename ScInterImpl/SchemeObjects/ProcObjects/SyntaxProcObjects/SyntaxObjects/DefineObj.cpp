#include"DefineObj.hpp"
#include"../../../SymbolObj.hpp"
#include"../../LambdaObj.hpp"

DefineObj::~DefineObj(){
#ifdef DEBUG
  std::cout << "define destructor " + id << std::endl;
#endif
  if(obj != NULL){
#ifdef DEBUG
    std::cout << "delete " << obj->print() << " " << obj << std::endl;
#endif    
    delete obj;
  }
#ifdef DEBUG
  std::cout << "define destructor end" << std::endl;
#endif
}

void DefineObj::set(Lexer& lex){}

void DefineObj::setId(std::string name){
  id = name;
}

void DefineObj::setId(Object* id_obj){
  if(id_obj->getType() != SYMBOL_OBJ){
    throw std::string("Symbol define error in Define Expression.");
  }  
  id = static_cast<SymbolObj*>(id_obj)->getId();
}


void setParam(LambdaObj* lambda, ListObj& params){
  ListObj::Iterator iter = params.begin();
  while(!iter.isEmpty()){
    Object* id_obj = iter.getObj();
    if(id_obj->getType() != SYMBOL_OBJ)
      throw std::string("Invalid parameter in lambda expression");
    SymbolObj* symbol_obj = static_cast<SymbolObj*>(id_obj);
    lambda->addParam(symbol_obj->getId());
    iter.next();
  }
}


void setBody(LambdaObj* lambda, ListObj& body){
  ListObj::Iterator iter = body.begin();
  while(!iter.isEmpty()){
    Object* body_obj = iter.getObj();
    lambda->addBody(body_obj->clone());
    iter.next();
  }
}

void setLambdaObj(LambdaObj* lambda, ListObj& params, ListObj& body){
   setParam(lambda, params);
   setBody(lambda, body);
}

// define 文のパラメータを受け取り設定する
void DefineObj::setFromListObj(ListObj& params){
  Object* head_obj = params.getHead();
  if(head_obj == NULL)
    throw std::string("define syntax error.");
  if(head_obj->getType() == LIST_OBJ){
    // 先頭の要素がリストのとき、関数定義
    ListObj* head_list = dynamic_cast<ListObj*>(head_obj);
    Object* id_obj = head_list->getHead();
    if(id_obj == NULL){
      delete head_obj;
      throw std::string("parameter is empty is define statement");
    }
    ListObj param_list = head_list->getTail();
    ListObj body_list = params.getTail();
    // 関数定義なのでLambda オブジェクトにパラメータとボディを設定する
    LambdaObj* lambda = new LambdaObj();
#ifdef DEBUG
    std::cout << "create lambda " << lambda << std::endl;
#endif
    try{
      // 関数名の設定
      setId(id_obj);
      // lambda オブジェクトの設定
      setLambdaObj(lambda, param_list, body_list);
    }catch(std::string& s){
      // パラメータがシンボルでない場合はエラーを受け取る
      delete head_obj;
      delete id_obj;
      delete lambda;
      throw s;
    }
    // lambda オブジェクトを設定する
    setObject(static_cast<Object*>(lambda));
    delete id_obj;
  }else if(head_obj->getType() == SYMBOL_OBJ){
    // 先頭がシンボルの時は変数定義
    // 変数名を設定する
    setId(head_obj);
   
    ListObj body_list = params.getTail();
    if(body_list.size() != 1){
      delete head_obj;
      throw std::string("A define statement has a one expression");
    }
    // 定義文を設定する
    ListObj::Iterator iter = body_list.begin();
    setObject(body_list.begin().getObj()->clone());
  }
  delete head_obj;
}


void DefineObj::setObject(Object* object){
  obj = object;
}

Object* DefineObj::eval(Env* env){
  Object* search_obj = env->searchInTop(id);
  if(search_obj != NULL){
    throw std::string("Already defined id: ") + id;
  }
  env->setSymbol(id, obj->eval(env));
  return NULL;
}

std::string DefineObj::print(){
  return "#define: " + id + " " + obj->print();
}

Object* DefineObj::clone(){
  DefineObj* ret = new DefineObj();
  ret->id = id;
  ret->obj = obj->clone();
  return ret;
}

