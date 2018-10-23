#define DEBUG
#include"ScInter.hpp"
#include<string>
#include<iostream>
using namespace std;

int main(int argc, char* argv[]){
  if(argc <= 1)
    return 0;
  string str(argv[1]);
  // プログラムの第一引数のファイルを読み込む
  ScInter scInt(str);
  // 初期化、ファイルを読み込みトークン化する
  scInt.init();
  while(!scInt.isEnd()){
    // 式を一つ実行し、実行結果の文字列を得る
    cout << "**********Eval: " << scInt.executeOneExp() << " *******" << endl;
  }
  return 0;
}
  
