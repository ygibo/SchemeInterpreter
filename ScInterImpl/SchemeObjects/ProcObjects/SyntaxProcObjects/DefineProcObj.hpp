#ifndef DEFINE_FACTORY
#define DEFINE_FACTORY

#include<string>
#include<iostream>
#include"../../Object.hpp"
#include"../../ListObj.hpp"
#include"../ProcObj.hpp"
#include"../../../Environment.hpp"

class DefineProcObj : public ProcObj{
public:
  DefineProcObj() : ProcObj() {}
  // �������Ȃ�
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  // define ���ւ̃p�����[�^��n���Adefine �������s����
  Object* execute(ListObj& param_list, Env* env);
};

#endif