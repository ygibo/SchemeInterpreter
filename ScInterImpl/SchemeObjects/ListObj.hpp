#ifndef LIST_OBJECT
#define LIST_OBJECT

#include"../Environment.hpp"
#include"Object.hpp"
#include"PairObj.hpp"
#include<string>

class ListNode;

class ListObj : public Object{
private:
  ListNode* head;
  ListNode* tail;
  bool isOriginal;
  int cnt;
public:
  class Iterator{
  private:
    friend ListObj;
    PairObj* node;
  public:
    Iterator(PairObj* node) : node(node) {}
    void next();
    Object* getObj();
    bool isEqual(Iterator& i);
    bool isEnd();
    bool isEmpty();
    void print();
  };
    
  ListObj();
  ~ListObj();
  void add(Object* obj);
  void addFront(Object* obj);
  Object* getHead();
  ListObj getTail();
  Object* eval(Env* e);
  std::string print();
  Object* clone();
  Iterator begin();
  bool isEnd(Iterator& i);
  bool isEmptyList();
  int size();
};

#endif
