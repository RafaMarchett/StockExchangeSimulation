#include "../headers/Menus.h"
#include "../headers/Market.h"
#include "../headers/SystemFunctions.h"
std::atomic<bool> isLoop{false};
Menus::Menus() {}
void Menus::changeStockOnScreen(bool newState) {
  Market tempMarket = Market::getMarket();
  tempMarket.setStockOnScreen(newState);
}

void Menus::firstInitialization() {
  char opt{'/'};
  SysFuncs SysFuncsManager;
  cout << clear;
  changeStockOnScreen(false);
  do {
    cout << "\nEnter 1 for English\n"
         << "Insira 2 para Portugues\n>>> " << std::flush;
    opt = SysFuncsManager.getSingleKey();
    if (opt == '1' || opt == '2') {
      language = opt;
      break;
    }
    cout << clear << "\nEnter a valid option\nInsira uma opção válida\n"
         << std::flush;
  } while (1);
}

void Menus::homeMenuOptions(char input) {
  switch (input) {
  case '1': {
    allStocksMenu();
    break;
  }

  default: {
    if (language == '1')
      cout << clear << "\nInsert a valid option" << std::endl;
    else if (language == '2')
      cout << clear << "\nInsira uma opção válida" << std::endl;
    cout << "\nIMP: " << input << std::endl;
  }
  }
  homeMenu();
}

void Menus::homeMenu() {
  changeStockOnScreen(false);
  SysFuncs SysFuncsManager;
  char tempInput{'/'};
  if (language == '1') {
    cout << clear << "\nEnter '1' to go to the " << bold << "\"Stock Market\" "
         << noBold << "menu\n"
         << ">>> " << std::flush;

    tempInput = SysFuncsManager.getSingleKey();
    homeMenuOptions(tempInput);
  } else if (language == '2') {
    cout << clear << "\nInsira '1' para ir ao menu" << bold
         << " \"Mercado de Ações\"\n"
         << noBold << ">>> " << std::flush;
    tempInput = SysFuncsManager.getSingleKey();
    homeMenuOptions(tempInput);
  } else
    exit(2);
}

void Menus::allStocksMenu() {
  cout << clear;
  shared_ptr<Market> tempMarket = std::make_shared<Market>(Market::getMarket());
  changeStockOnScreen(true);
  cout << std::endl;
  isLoop = true;
  std::jthread receiveEnter(inputToLoop);
  while (isLoop) {
    tempMarket->printAllStocks();
    printPressEnter();
    sleep(milliseconds(100));
  }
}

void Menus::inputToLoop() {
  SysFuncs funcsManager;
  funcsManager.pressEnterToContinue();
  isLoop = false;
}
