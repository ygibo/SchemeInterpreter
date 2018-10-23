//#define DEBUG
#include"ListObj.hpp"
#include"ProcObjects/ProcObj.hpp"
#include<iostream>

class ListNode{
 public:
  ListNode() : pair_obj(NULL), prev(NULL) {}
  ListNode(PairObj* obj, ListNode* prev) : pair_obj(obj), prev(prev){}
  ~ListNode(){}
  
  PairObj* pair_obj;
  ListNode* prev;
  ListNode* next;
};

void ListObj::Iterator::next(){
  if(node != NULL && !node->isEmpty())
    node = dynamic_cast<PairObj*>(node->getCdr());
}

Object* ListObj::Iterator::getObj(){
  if(node != NULL)
    return node->getCar();
  return NULL;
}

bool ListObj::Iterator::isEqual(Iterator& i){
  return node == i.node;
}

bool ListObj::Iterator::isEnd(){
  return node == NULL;
}

void ListObj::Iterator::print(){
  std::cout << node->print() << std::endl;
}


bool ListObj::Iterator::isEmpty(){
  return node->isEmpty();
}

ListObj::ListObj() : Object(LIST_OBJ), cnt(0) {
#ifdef DEBUG
  std::cout << "list create " << this << std::endl;
#endif
  isOriginal = true;
  head = new ListNode();
  tail = new ListNode();
  PairObj* head_pair = new PairObj();
  PairObj* tail_pair = new PairObj();
  head_pair->setCar(NULL);
  head_pair->setCdr(tail_pair);
  head->pair_obj = head_pair;
  head->prev = NULL;
  head->next = tail;
  
  tail_pair->setCar(NULL);
  tail_pair->setCdr(NULL);
  tail->pair_obj = tail_pair;
  tail->prev = head;
  tail->next = NULL;
}



ListObj::~ListObj(){
#ifdef DEBUG
  std::cout << "list destructor " << this  << std::endl;
  std::cout << (isOriginal ? "original" : "not original") << std::endl;
#endif
  if(isOriginal){
    delete head->pair_obj;
    ListNode* node_obj = tail->prev;;
    while(node_obj != head){
      ListNode* pre = node_obj->prev;
      delete node_obj;
      node_obj = pre;
      pre = node_obj->prev;
    }
    delete tail;
  }
}

void ListObj::add(Object* obj){
  ListNode* node = new ListNode();
  node->pair_obj = new PairObj();
  
  node->pair_obj->setCar(obj);
  node->pair_obj->setCdr(tail->pair_obj);
  node->next = tail;
  node->prev = tail->prev;
  tail->prev->pair_obj->setCdr(node->pair_obj);
  tail->prev->next = node;
  tail->prev = node;
  ++cnt;
}

void ListObj::addFront(Object* obj){
  ListNode* node = new ListNode();
  node->pair_obj = new PairObj();

  node->pair_obj->setCar(obj);
  node->pair_obj->setCdr(head->pair_obj->getCdr());
  node->prev = head;
  node->next = head->next;
  
  head->pair_obj->setCdr(node->pair_obj);
  head->next->prev = node;
  head->next = node;
  ++cnt;
}

Object* ListObj::getHead(){
  if(head->pair_obj->getCdr() == tail->pair_obj)
    return NULL;
  PairObj* head_pair = dynamic_cast<PairObj*>(head->pair_obj->getCdr());
  return head_pair->getCar()->clone();
}

ListObj ListObj::getTail(){
  ListObj ret;
  
  ret.cnt = 0;
  ret.isOriginal = false;
  
  delete ret.head->pair_obj;
  delete ret.head;
  delete ret.tail;
  if(cnt == 0){
    ret.head = head;
    ret.tail = tail;
  }else if(cnt == 1){
    ret.head = head->next;
    ret.tail = tail;
  }else{
    ret.cnt = cnt - 1;
    ret.head = head->next;
    ret.tail = tail;
  }
  return ret;
}

ProcObj* getProcedure(Object* obj, Env* env){
  Env env_for_head(env);
  Object* evaluated_obj = NULL;
  evaluated_obj = obj->eval(&env_for_head);
  
  if(evaluated_obj->getType() != PROC_OBJ){
    delete evaluated_obj;
    throw std::string("The first element of the list is not a function.");
  }
  return dynamic_cast<ProcObj*>(evaluated_obj);
}

Object* ListObj::eval(Env* env){
#ifdef DEBUG
  std::cout << "list eval" << std::endl;
#endif
  if(begin().isEmpty())
    throw std::string("Can't evaluate empty list");
  
  Object* obj = getHead();
  ProcObj* proc_obj = NULL;
  try{
    // 先頭の要素を評価し取得、関数でないとエラーを投げる
    proc_obj = getProcedure(obj, env);
  }catch(std::string& s){
    delete obj;
    throw s;
  }
  
  Object* ans = NULL;
  ListObj parameter = getTail(); // 関数の引数
  try{
#ifdef DEBUG
    std::cout << "list execute" << std::endl;
    std::cout << proc_obj->print() << std::endl;
    std::cout << parameter.print() << std::endl;
#endif
    // 関数を実行する
    ans = proc_obj->execute(parameter, env);
    
#ifdef DEBUG
    if(ans != NULL)
      std::cout << "ans " << ans << " " << ans->print() << std::endl;
    else
      std::cout << "ans is NULL" << std::endl;
    std::cout << "list execute end" << std::endl;
#endif
  }catch(std::string& s){
    delete obj;
    delete proc_obj;
    throw s;
  }
  delete obj;
  delete proc_obj;
  return ans;
}

std::string ListObj::print(){
  // リストの各要素を括弧に挟んで表示する
  std::string ret;
  Iterator iter = begin();
  while(!iter.isEmpty()){
    Object* o = iter.getObj();
    ret += o->print() + " ";
    iter.next();
  }
  if(ret.length() >= 1)
    ret[ret.length() - 1] = ')';
  else
    ret += ')';
  return "(" + ret;
}

Object* ListObj::clone(){
  // リストの各要素を複製しリストにして返す
  ListObj* ret = new ListObj();
  ret->isOriginal = true;
  
  Iterator iter = begin();
  while(!iter.isEmpty()){
    Object* o = iter.getObj()->clone();
    ret->add(o);
    iter.next();
  }
  return ret;
}

ListObj::Iterator ListObj::begin(){
  PairObj* p  = dynamic_cast<PairObj*>(head->pair_obj->getCdr());
  return Iterator(p);
}

int ListObj::size(){
  return cnt;
}
