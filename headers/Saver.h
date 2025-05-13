#pragma once
#include "header.hpp"
#ifndef SAVER
#define SAVER
#define ERROR_FILE 150
#define CLASS_NOT_RECEIVED 151

class Saver {
public:
  template <typename... Args> static void saveAllClasses(Args &&...);
  template <typename... Args> static void readAllClasses(Args &&...);

private:
  template <typename T> static void saveClass(T &);
  template <typename T> static void readClass(T &);
  void truncFile();

  template <typename T> static void saveElement(std::ofstream &, vector<T> &);
  template <typename T>
  static void saveElement(std::ofstream &, std::stack<T> &);
  template <typename T> static void saveElement(std::ofstream &, T &);

  template <IsStruct T> static void saveElement(std::ofstream &, T &);
  template <IsStruct T>
  static void saveElement(std::ofstream &, shared_ptr<T> &);
  template <typename key, typename value>
  void static saveElement(std::ofstream &, std::unordered_map<key, value> &);

  void static saveElement(std::ofstream &, string &);
  std::ofstream static saveFile();
  std::ifstream static readFile();

  void static readElement(std::ifstream &, string &);
  template <typename T> void static readElement(std::ifstream &, vector<T> &);
  template <typename T>
  void static readElement(std::ifstream &, std::stack<T> &);
  template <typename T> void static readElement(std::ifstream &, T &);

  template <typename key, typename value>
  void static readElement(std::ifstream &, std::unordered_map<key, value> &);
  template <IsStruct T> void static readElement(std::ifstream &, T &);
  template <IsStruct T>
  void static readElement(std::ifstream &, shared_ptr<T> &);
  template <typename T, typename Func, std::size_t... Is>
  void static forEachImpl(T &&t, Func fn, std::index_sequence<Is...>);

  template <typename... Args, typename Func>
  void static forEachInTuple(const std::tuple<Args...> &t, Func fn);
  void static notClass();

  void static createFile();
};
#include "Saver_Templates.hpp"
#endif // SAVER
