#pragma once
#include "header.hpp"
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
  static void changeStockOnScreen(bool);
  static void homeMenuOptions(char);
  static void inputToLoop();
  static void enterSingleChar(char &);
  static inline void specificStockLoop(sharedStock &, char &);

  static void allStocksMenu();
  static void specificStock();
  static void fullPortifolioMenu();
};
inline std::atomic<bool> isLoop{false};
#include "Portifolio.h"
void Menus::specificStockLoop(sharedStock &stock, char &opt) {
  Portifolio userPortifolio = Portifolio::getPortifolio();
  cout << clear;
  stock->printStockInMarket();
  printInLanguage("\nEnter '1' to buy the Stock\nEnter '2' to sell the "
                  "Stock\nPress 'enter' to exit\n>>> ",
                  "\nInsira '1' para comprar a ação\nInsira '2' para vender a "
                  "ação\nPressione 'enter' para sair\n>>> ");
  enterSingleChar(opt);
  if (!isLoop) {
    switch (opt) {
    case '1': {
      printInLanguage("Insert the Stock quantity\n>>> ",
                      "Insira a quantidade de ações\n>>> ");
      int32_t stockQuantity;
      cin >> stockQuantity;
      if (stockQuantity >= 0)
        userPortifolio.buyStock(stock, stockQuantity);
      else
        printInLanguage(
            "Cannot buy negative quantity of stocks\n",
            "Impossivel comprar uma quantidade negativa de ações\n");
      break;
    }
    case '2': {
      break;
    }
    case '\n': {
      break;
    }
    default: {
      printInLanguage("Invalid key\n", "Chave inválida\n");
      break;
    }
    }
  }
}
#endif // MENUS
