#pragma once
#include "header.hpp"
#ifndef MENUS
#define MENUS
class Menus {
public:
  static void homeMenu() {
    cout << "ha\n";
    changeStockOnScreen(false);
  }
  static void allStocksMenu() {}
  // static void (); menu de negociacao
private:
  static void changeStockOnScreen(bool);
};
#include "../src/Menus.cpp"
#endif // MENUS
