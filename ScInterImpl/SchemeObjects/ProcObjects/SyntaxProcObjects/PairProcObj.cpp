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
  // cons �̈������Q�łȂ��ƃG���[
  if(param_list.size() != 2)
    throw std::string("cons procedure expects 2 arguments");
  
  ListObj::Iterator iter = param_list.begin();
 
  Object* car = NULL; // ��������]�����ݒ肷��
  if(iter.getObj() != NULL){
    Env new_env(env);
    car = iter.getObj()->eval(&new_env);
  }
  if(car == NULL){
    throw std::string("Cons statement parameter is null.");
  }			

  iter.next();
 
  Object* cdr = NULL; // ��������]�����ݒ肷��
  if(iter.getObj() != NULL){
    Env new_env(env);
    cdr = iter.getObj()->eval(&new_env);
  }
  if(cdr == NULL){
    delete car;
    throw std::string("Cons statement parameter is null.");
  }
  
  if(cdr->getType() == LIST_OBJ){
    // �����������X�g�������炻��ɒǉ�����
    ListObj* ret = dynamic_cast<ListObj*>(cdr);
    ret->addFront(car);
    return ret;
  }else if(cdr->getType() == PAIR_OBJ){
    PairObj* pair = dynamic_cast<PairObj*>(cdr);
    if(pair->isEmpty()){
      // ���������y�A�[��'()�������烊�X�g�ɂ��ĕԂ�
      ListObj* ret = new ListObj();
      ret->addFront(car);
      delete cdr;
      return ret;
    }
  }
  // ���ʂɃy�A�[�ɂ��ĕԂ�
  PairObj* pair_obj = new PairObj();
  pair_obj->setCar(car);
  pair_obj->setCdr(cdr);
  return pair_obj;
}