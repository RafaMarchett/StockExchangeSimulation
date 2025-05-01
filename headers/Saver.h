#pragma once
#include "header.hpp"
#ifndef SAVER
#define SAVER
#define ERROR_FILE 150
#define CLASS_NOT_RECEIVED 151

class Saver {
public:
  // void _saveFile(Tst&);
  // void _readFile(Tst&);
  template <typename T> void saveClass(T &);
  template <typename T> void readClass(T &);
  void truncFile();

  //////////////////////////////////////////////////////////////////////////
  template <typename T> void saveElement(std::ofstream &, vector<T> &);
  template <typename T> void saveElement(std::ofstream &, T &);

  template <IsStruct T> void saveElement(std::ofstream &, T &);
  template <typename key, typename value>
  void saveElement(std::ofstream &, std::unordered_map<key, value> &);

  void saveElement(std::ofstream &, string &);
  std::ofstream saveFile();
  std::ifstream readFile();

  void readElement(std::ifstream &, string &);
  template <typename T> void readElement(std::ifstream &, vector<T> &);
  template <typename T> void readElement(std::ifstream &, T &);

  template <typename key, typename value>
  void readElement(std::ifstream &, std::unordered_map<key, value> &);
  template <IsStruct T> void readElement(std::ifstream &, T &);

private:
  template <typename T, typename Func, std::size_t... Is>
  void forEachImpl(T &&t, Func fn, std::index_sequence<Is...>);

  template <typename... Args, typename Func>
  void forEachInTuple(const std::tuple<Args...> &t, Func fn);

  void createFile();
  string fileName = "save.dat";
};
#include "Saver_Templates.hpp"
#endif // SAVER
