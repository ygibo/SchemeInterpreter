#include"PairProcObj.hpp"
#include"../../PairObj.hpp"


Object* PairProcObj::eval(Env* env){
  return clone();
}

std::string PairProcObj::print(){
  return std::string("(#cons factory)");
}

Object* PairProcObj::clone(){
  return new PairProcObj();
}

Object* PairProcObj::execute(ListObj& param_list, Env* env){
  // cons の引数が２つでないとエラー
  if(param_list.size() != 2)
    throw std::string("cons procedure expects 2 arguments");
  
  ListObj::Iterator iter = param_list.begin();
 
  Object* car = NULL; // 第一引数を評価し設定する
  if(iter.getObj() != NULL){
    Env new_env(env);
    car = iter.getObj()->eval(&new_env);
  }
  if(car == NULL){
    throw std::string("Cons statement parameter is null.");
  }			

  iter.next();
 
  Object* cdr = NULL; // 第二引数を評価し設定する
  if(iter.getObj() != NULL){
    Env new_env(env);
    cdr = iter.getObj()->eval(&new_env);
  }
  if(cdr == NULL){
    delete car;
    throw std::string("Cons statement parameter is null.");
  }
  
  if(cdr->getType() == LIST_OBJ){
    // 第二引数がリストだったらそれに追加する
    ListObj* ret = dynamic_cast<ListObj*>(cdr);
    ret->addFront(car);
    return ret;
  }else if(cdr->getType() == PAIR_OBJ){
    PairObj* pair = dynamic_cast<PairObj*>(cdr);
    if(pair->isEmpty()){
      // 第二引数がペアーで'()だったらリストにして返す
      ListObj* ret = new ListObj();
      ret->addFront(car);
      delete cdr;
      return ret;
    }
  }
  // 普通にペアーにして返す
  PairObj* pair_obj = new PairObj();
  pair_obj->setCar(car);
  pair_obj->setCdr(cdr);
  return pair_obj;
}
