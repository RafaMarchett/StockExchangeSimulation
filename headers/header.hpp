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
#include <memory>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

using std::ostream, std::cout, std::cin, std::string, std::shared_ptr,
    std::shared_ptr, std::make_shared, std::vector, std::setw;

const string upArrow{"\033[32m▲\033[37m"}, downArrow{"\033[31m▼\033[37m"};

const string fileName = "save.dat";

inline static ostream &bold(ostream &manip) { return manip << "\033[1m"; }
inline static ostream &noBold(ostream &manip) { return manip << "\033[0m"; }
inline static ostream &clear(ostream &manip) {
  return manip << "\033[2J" << "\033[H";
}
inline static void maxCinIgnore() {
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline static void configureFloat() {
  cout << std::fixed << std::setprecision(2);
}

template <typename T> inline static void inputIgnore(T &input) {
  cin >> input;
  cin.ignore(10000, '\n');
}

inline char language;

inline void printPressEnter() {
  if (language == '1') {
    cout << "Press 'Enter' to continue... ";
  } else {
    cout << "Pressione 'Enter' para continuar... ";
  }
  cout << std::flush;
}

template <typename ABC>
concept IsStruct = std::is_class_v<ABC>;

#endif
