#pragma once
#include "header.hpp"
#ifndef MENUS
#define MENUS
class Menus {
public:
  static void firstInitialization();
  static void homeMenu();

private:
  Menus();
  static void voidMenu();
  static void allStocksMenu();
  static void changeStockOnScreen(bool);
  static void homeMenuOptions(char);
  static void inputToLoop();
};
#endif // MENUS
