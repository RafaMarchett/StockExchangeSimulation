#include "../headers/Menus.h"
#include <functional>
Menus::Menus() {}
void Menus::changeStockOnScreen(bool newState) {
  Market tempMarket = Market::getMarket();
  tempMarket.setStockOnScreen(newState);
}

void Menus::firstInitialization() {
  char opt{'/'};
  changeStockOnScreen(false);
  do {
    cout << "\nEnter 1 for English\n"
         << "Insira 2 para Portugues\n>>> " << std::flush;
    inputIgnore(opt);
    if (opt == '1' || opt == '2') {
      language = opt;
      break;
    }
    cout << "\nEnter a valid option\nInsira uma opção válida\n" << std::flush;
  } while (1);
  homeMenu();
}

std::function<void()> Menus::homeMenuOptions(char input) {
  switch (input) {
  case '1': {
    return allStocksMenu();
    break;
  }
  case ' ':
  case '\n':
  case '\t':
    break;

  default: {
    if (language == '1')
      cout << "\nInsert a valid option\n";
    else if (language == '2')
      cout << "\nInsira uma opção válida\n";
    homeMenu();
    break;
  }
  }
  return nullptr;
}

std::function<void()> Menus::homeMenu() {
  changeStockOnScreen(false);
  char tempInput{'/'};
  if (language == '1') {
    cout << "\nEnter '1' to go to the " << bold << "\"Stock Market\" " << noBold
         << "menu\n"
         << ">>> " << std::flush;

    inputIgnore(tempInput);
    return homeMenuOptions(tempInput);
  } else if (language == '2') {
    cout << "\nInsira '1' para ir ao menu" << bold << " \"Mercado de Ações\"\n"
         << noBold << ">>> " << std::flush;
    inputIgnore(tempInput);
    return homeMenuOptions(tempInput);
  } else
    exit(2);
  return nullptr;
}
std::function<void()> Menus::allStocksMenu() {
  shared_ptr<Market> tempMarket = std::make_shared<Market>(Market::getMarket());
  changeStockOnScreen(1);
  if (language == '1') {
    cout << bold << "\n### STOCK MARKET ###" << noBold;
  } else if (language == '2') {
    cout << bold << "\n### MERCADO DE AÇÕES ### " << noBold;
  }

  cout << std::endl;
  std::function<void()> returnMenu = [tempMarket]() {
    tempMarket->printAllStocks();
  };
  return returnMenu;
}
