#pragma once
#include "Market.h"
#include "header.hpp"
#ifndef MENUS
#define MENUS
class Menus {
public:
  static void firstInitialization();
  static std::function<void()> homeMenu();

private:
  Menus();
  static void voidMenu();
  static std::function<void()> allStocksMenu();
  static void changeStockOnScreen(bool);
  static std::function<void()> homeMenuOptions(char);
};
#endif // MENUS
