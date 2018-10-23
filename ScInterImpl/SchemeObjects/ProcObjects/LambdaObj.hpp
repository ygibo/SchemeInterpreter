#ifndef LAMBDA_OBJECT
#define LAMBDA_OBJECT

#include<vector>
#include<string>
#include"../../Environment.hpp"
#include"../../Lexer/Lexer.hpp"
#include"ProcObj.hpp"
#include"../ListObj.hpp"

// Lambda ����\���I�u�W�F�N�g
class LambdaObj : public ProcObj{
private:
  std::vector<std::string> paramName; // �p�����[�^��
  std::vector<Object*> body; // lambda ���� body
public:
  LambdaObj() : ProcObj("lambda") {}
  ~LambdaObj();
  // �p�����[�^��ǉ�
  void addParam(std::string name);
  // lambda ���� body ��ǉ�
  void addBody(Object* obj);
  Object* clone();
  // lambda ���ւ̈����Ɗ�������Ď��s����
  Object* execute(ListObj& paramList, Env* e);
  std::string print();
};

#endif