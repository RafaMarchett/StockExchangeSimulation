#pragma once
#ifndef HEADER_HPP
#define HEADER_HPP

#include <chrono>
#include <concepts>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

using std::ostream, std::cout, std::cin, std::string, std::shared_ptr,
    std::shared_ptr, std::make_shared, std::vector, std::setw;
#define LANGUAGE_NOT_FIND 2
#define MS_ERROR_SLEEP 1500
inline char language;

const string upArrow{"\033[32m▲\033[37m"}, downArrow{"\033[31m▼\033[37m"};

const string fileName = "save.dat";

inline static ostream &bold(ostream &manip) {
  return manip << "\033[37m\033[1m";
}
inline static ostream &noBold(ostream &manip) { return manip << "\033[0m"; }
inline static ostream &greenOutput(ostream &manip) {
  return manip << "\033[32m";
}
inline static ostream &redOutput(ostream &manip) { return manip << "\033[31m"; }
inline static ostream &clear(ostream &manip) {
  return manip << "\033[2J" << "\033[H";
}
inline static void maxCinIgnore() {
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline static void configureDouble() {
  cout << std::fixed << std::setprecision(2);
}

template <typename T> inline static void inputIgnore(T &input) {
  cin >> input;
  cin.ignore(10000, '\n');
}

void initializeLanguage();
void printInLanguage(const string &string1, const string &string2);

struct Ternary {
  signed int value : 2;

  void operator=(signed int input) { set(input); }
  void set(int input) {
    if (input < -1 || input > 1) {
      std::cerr << "Error, overflow of 'Ternary', the value " << input
                << " is too large" << std::endl;
    } else {
      value = input;
    }
  }
  signed int get() const { return value; }
};

inline void printPressEnter() {
  printInLanguage("Press 'Enter' to continue... ",
                  "Pressione 'Enter' para continuar... ");
}

template <typename T>
concept HasToTuple = requires(T a) {
  { a.toTuple() };
};
template <typename T>
concept IsStruct = std::is_class_v<T> && HasToTuple<T>;

template <typename T>
concept IsClass = std::is_class_v<T>;

template <typename T>
concept IsMapLike = requires(T mp) {
  typename T::key_type;
  typename T::mapped_type;
  { mp.begin() } -> std::input_or_output_iterator;
  { mp.end() } -> std::input_or_output_iterator;
};
template <typename T>
concept IsTrivial = std::is_trivially_copyable_v<T> && !std::is_class_v<T>;
#endif // HEADER_HPP
