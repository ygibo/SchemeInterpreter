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
  // 読み込むファイルの名前を渡す
  ScInter(std::string fileName);
  // ファイルを読み込み、トークン化する
  void init();
  // ファイル名の設定
  void setFile(std::string fileName);
  // 最後まで実行したか？ エラー時には true を返す
  bool isEnd();
  // 式を一つだけ実行する, エラーが発生しているときは実行しない
  std::string executeOneExp();
};

#endif
