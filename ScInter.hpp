#ifndef SCHEME_INTEPRETER
#define SCHEME_INTEPRETER

#include<string>
#include"ScInterImpl/Lexer/Lexer.hpp"
#include"ScInterImpl/Environment.hpp"

class ScInter{
private:
  std::string file_name;
  Lexer lex;
  Env env;
  bool isErrorOccur;
public:
  // �ǂݍ��ރt�@�C���̖��O��n��
  ScInter(std::string fileName);
  // �t�@�C����ǂݍ��݁A�g�[�N��������
  void init();
  // �t�@�C�����̐ݒ�
  void setFile(std::string fileName);
  // �Ō�܂Ŏ��s�������H �G���[���ɂ� true ��Ԃ�
  bool isEnd();
  // ������������s����, �G���[���������Ă���Ƃ��͎��s���Ȃ�
  std::string executeOneExp();
};

#endif