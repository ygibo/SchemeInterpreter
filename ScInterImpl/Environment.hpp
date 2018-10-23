#ifndef SCHEME_ENVIRONMENT
#define SCHEME_ENVIRONMENT
#include<string>
#include<map>
#include"SchemeObjects/Object.hpp"

class Object;


//プログラム実行時の環境、シンボルネームとオブジェクトの対応を保持する
class Env{
private:
  std::map<std::string, Object*> symbolTable;
  Env* preEnv;
public:
  Env();
  // 環境 e の上の環境を作る。一番上の環境からシンボルを探す。また、一番上の環境のみに
  Env(Env* e) : preEnv(e) {}
  ~Env();
  // シンボルにオブジェクトを対応付ける。オブジェクトの所有権は Env に移る
  void setSymbol(std::string name, Object* def);
  // 全ての環境を探索し、name に対応したオブジェクトを返す。ない場合は NULL を返す
  Object* searchSymbol(std::string name);
  // 一番上の環境のみ探索し、対応するオブジェクトを返す。ない場合は NULL を返す
  Object* searchInTop(std::string name);
  // 環境の内容の表示。
  void show();
};

#endif
