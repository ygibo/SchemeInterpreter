#ifndef SCHEME_ENVIRONMENT
#define SCHEME_ENVIRONMENT
#include<string>
#include<map>
#include"SchemeObjects/Object.hpp"

class Object;


//�v���O�������s���̊��A�V���{���l�[���ƃI�u�W�F�N�g�̑Ή���ێ�����
class Env{
private:
  std::map<std::string, Object*> symbolTable;
  Env* preEnv;
public:
  Env();
  // �� e �̏�̊������B��ԏ�̊�����V���{����T���B�܂��A��ԏ�̊��݂̂�
  Env(Env* e) : preEnv(e) {}
  ~Env();
  // �V���{���ɃI�u�W�F�N�g��Ή��t����B�I�u�W�F�N�g�̏��L���� Env �Ɉڂ�
  void setSymbol(std::string name, Object* def);
  // �S�Ă̊���T�����Aname �ɑΉ������I�u�W�F�N�g��Ԃ��B�Ȃ��ꍇ�� NULL ��Ԃ�
  Object* searchSymbol(std::string name);
  // ��ԏ�̊��̂ݒT�����A�Ή�����I�u�W�F�N�g��Ԃ��B�Ȃ��ꍇ�� NULL ��Ԃ�
  Object* searchInTop(std::string name);
  // ���̓��e�̕\���B
  void show();
};

#endif