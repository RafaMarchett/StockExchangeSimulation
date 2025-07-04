#pragma once
#ifndef MENUS
#define MENUS
#include "Stock.h"
class Menus {
public:
  static void firstInitialization();
  static void homeMenu();

private:
  Menus();
  static void voidMenu();
  static void homeMenuOptions(char);
  static void inputToLoop();
  static void enterSingleChar(char &);
  static void specificStockSwitch(sharedStock &, char &);

  static void allStocksMenu();
  static void specificStock(sharedStock stock = nullptr);
  static void fullPortifolioMenu();
  static void allTransactionsMenu();
  static void marketNoticesMenu();
  static void saveAndExit();
};
#endif // MENUS
