#ifndef QUOTE_OBJECT
#define QUOTE_OBJECT

#include"../Environment.hpp"
#include"Object.hpp"

class QuoteObj : public Object{
private:
  Object* exp;
public:
  QuoteObj();
  QuoteObj(Object* quotedExp);
  ~QuoteObj();
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  void set(Object* obj);
};

#endif
