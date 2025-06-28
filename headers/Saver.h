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
  static void saveElement(std::ofstream &, const string &);
  static void readElement(std::ifstream &, string &);

  template <typename T> static void saveClass(std::ofstream &, T &);
  template <typename T> static void readClass(std::ifstream &, T &);
  static void truncFile();

  template <typename T> static void saveElement(std::ofstream &, vector<T> &);
  template <typename T>
  static void saveElement(std::ofstream &, std::stack<T> &);
  template <IsTrivial T> static void saveElement(std::ofstream &, T &);

  template <IsStruct T> static void saveElement(std::ofstream &, T &);
  template <IsClass T>
  static void saveElement(std::ofstream &, shared_ptr<T> &);
  template <typename Key, typename Value>
  static void saveElement(std::ofstream &File, std::map<Key, Value> &inputMap);

  template <typename Key, typename Value>
  static void saveElement(std::ofstream &File,
                          std::unordered_map<Key, Value> &inputMap);
  std::ofstream static saveFile();
  std::ifstream static readFile();

  template <typename T> void static readElement(std::ifstream &, vector<T> &);
  template <typename T>
  void static readElement(std::ifstream &, std::stack<T> &);
  template <IsTrivial T> void static readElement(std::ifstream &, T &);

  template <typename Key, typename Value>
  void static readElement(std::ifstream &, std::map<Key, Value> &);
  template <typename Key, typename Value>
  void static readElement(std::ifstream &, std::unordered_map<Key, Value> &);
  template <IsStruct T> void static readElement(std::ifstream &, T &);
  template <IsClass T>
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
