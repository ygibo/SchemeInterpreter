#define DEBUG
#include"ScInter.hpp"
#include<string>
#include<iostream>
using namespace std;

int main(int argc, char* argv[]){
  if(argc <= 1)
    return 0;
  string str(argv[1]);
  // �v���O�����̑������̃t�@�C����ǂݍ���
  ScInter scInt(str);
  // �������A�t�@�C����ǂݍ��݃g�[�N��������
  scInt.init();
  while(!scInt.isEnd()){
    // ��������s���A���s���ʂ̕�����𓾂�
    cout << "**********Eval: " << scInt.executeOneExp() << " *******" << endl;
  }
  return 0;
}
  