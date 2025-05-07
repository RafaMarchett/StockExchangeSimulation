#include "../headers/Menus.h"
#include "../headers/Market.h"
#include "../headers/Portifolio.h"
#include "../headers/SystemFunctions.h"
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
  case '2': {
    specificStock();
    break;
  }
  case '3': {
    fullPortifolioMenu();
    break;
  }

  default: {
    printInLanguage("\nInsert a valid option\n", "\nInsira uma opção válida\n");
  }
  }
  homeMenu();
}

void Menus::homeMenu() {
  changeStockOnScreen(false);
  SysFuncs SysFuncsManager;
  char tempInput{'/'};
  cout << clear;
  printInLanguage(
      "\nEnter '1' to go to the \"Stock Market\" menu\nEnter '2' to go to the "
      "\"Single Stock\" menu\nEnter '3' to go to the \"Full Portifolio\" "
      "menu\n",
      "\nInsira '1' para ir ao menu \"Mercado de Ações\"\nInsira '2' para ir "
      "ao menu \"Ação única\"\nInsira '3' para ir ao menu \"Portifolio "
      "Completo\"\n");

  tempInput = SysFuncsManager.getSingleKey();
  homeMenuOptions(tempInput);
  cout << ">>> " << std::flush;
  tempInput = SysFuncsManager.getSingleKey();
  homeMenuOptions(tempInput);
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

void Menus::specificStock() {
  string inputTicker;
  auto mkt = Market::getMarket();
  sharedStock stock = nullptr;
  printInLanguage("Enter a stock ticker\n>>> ",
                  "Insira o ticker de uma ação\n>>> ");
  cin >> inputTicker;
  stock = mkt.findTicker(inputTicker);
  char opt{'/'};
  // std::jthread receiveChar(enterSingleChar, std::ref(opt));
  isLoop = true;
  if (stock) {
    // print stock e adicionar funcionalidades de compra/venda
    while (isLoop) {
      specificStockLoop(stock, opt);
      sleep(milliseconds(100));
    }
  } else {
    cout << clear;
    printInLanguage("Non-existent stock ticker\n",
                    "Ticker de ação inexistente\n");
    specificStock();
  }
}

void Menus::fullPortifolioMenu() {
  SysFuncs funcsManager;
  Portifolio portifolioInstance = Portifolio::getPortifolio();
  portifolioInstance.printFullPortifolio();
  funcsManager.pressEnterToContinue();
}

void Menus::enterSingleChar(char &input) {
  SysFuncs funcsManager;
  char temp = funcsManager.getSingleKey();
  isLoop = false;
  input = temp;
}
