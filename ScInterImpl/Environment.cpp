#include"Environment.hpp"
#include<iostream>

Env::Env() : preEnv(NULL){
#ifdef DEBUG
  std::cout << "---------- Env start ----------" << this << std::endl;
#endif
}

Env::~Env() {
#ifdef DEBUG
  std::cout << "Env destructor" << std::endl;
  std::cout << this << std::endl;
#endif
  std::map<std::string, Object*>::iterator iter = symbolTable.begin();
  while(iter != symbolTable.end()){
#ifdef DEBUG
    std::cout << iter->first << " " << iter->second << std::endl;
#endif
    if(iter->second != NULL){
#ifdef DEBUG
      std::cout << "delete " << iter->second << std::endl;
      std::cout << iter->second->print() << std::endl;
#endif
      delete iter->second;
    }
    ++iter;
  }
#ifdef DEBUG
  std::cout << "Env destructor end" << std::endl;
#endif
}

void Env::show(){
  std::cout << "Env show" << std::endl;
  std::map<std::string, Object*>::iterator iter = symbolTable.begin();
  while(iter != symbolTable.end()){
    std::cout << "name " << iter->first << " ";
    if(iter->second != NULL)
      std::cout << iter->second->print();
    std::cout << std::endl;
    ++iter;
  }
  std::cout << "show end" << std::endl;
}


void Env::setSymbol(std::string name, Object* def){
#ifdef DEBUG
  std::cout << "Env set " << name << " -> " << def->print() << std::endl;
  std::cout << "Env is " << this << ",Object is " << def << std::endl;
#endif
  symbolTable[name] = def;
}

Object* Env::searchSymbol(std::string name){
  Object* ret = NULL;
  Env* cur = this;
  while(cur != NULL){
    ret = cur->symbolTable[name];
    if(ret != NULL)
      break;
    cur = cur->preEnv;
  }
  return ret;
}

Object* Env::searchInTop(std::string name){
  return symbolTable[name];
}
