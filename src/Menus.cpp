#include "../headers/Menus.h"
#include "../headers/Market.h"
#include "../headers/Portifolio.h"
#include "../headers/SystemFunctions.h"
#include "../headers/Tick.h"
inline std::atomic<bool> isLoop{false};
Menus::Menus() {}
void Menus::changeStockOnScreen(bool newState) {
  Market &tempMarket = Market::getMarket();
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
  case '4': {
    allTransactionsMenu();
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
      "Enter '1' to go to the \"Stock Market\" menu\nEnter '2' to go to the "
      "\"Single Stock\" menu\nEnter '3' to go to the \"Full Portifolio\" "
      "menu\nEnter '4' to go to the \"All Transactions\" menu\n",
      "Insira '1' para ir ao menu \"Mercado de Ações\"\nInsira '2' para ir "
      "ao menu \"Ação única\"\nInsira '3' para ir ao menu \"Portifolio "
      "Completo\"\nInsira '4' para ir ao menu \"Todas as Transações\"\n");

  tempInput = SysFuncsManager.getSingleKey();
  homeMenuOptions(tempInput);
  cout << ">>> " << std::flush;
  tempInput = SysFuncsManager.getSingleKey();
  homeMenuOptions(tempInput);
}

void Menus::allStocksMenu() {
  cout << clear;
  shared_ptr<Market> tempMarket(&Market::getMarket(), [](Market *) {});
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
  auto &mkt = Market::getMarket();
  sharedStock stock = nullptr;
  cout << clear;
  printInLanguage(
      "Enter a stock ticker, or type \"exit\" to exit\n>>> ",
      "Insira o ticker de uma ação ou digite \"exit\" para sair\n>>> ");
  cin >> inputTicker;
  if (inputTicker == "exit")
    return;
  stock = mkt.findTicker(inputTicker);
  char opt{'/'};
  isLoop = true;
  if (stock) {
    bool x = true;
    std::thread loopPrints([&]() {
      while (x) {
        cout << clear;
        stock->printStockInMarket();
        printInLanguage("\nSector: ", "\nSetor: ");
        cout << stock->getSector() << std::endl;
        printInLanguage(
            "\nEnter '1' to buy the Stock\nEnter '2' to sell the "
            "Stock\nPress 'enter' to exit\n>>> ",
            "\nInsira '1' para comprar a ação\nInsira '2' para vender a "
            "ação\nPressione 'enter' para sair\n>>> ");
        sleep(std::chrono::milliseconds(100));
      }
    });
    enterSingleChar(opt);
    x = false;
    loopPrints.join();

    specificStockSwitch(stock, opt);
  } else {
    cout << clear;
    printInLanguage("Non-existent stock ticker\n",
                    "Ticker de ação inexistente\n");
    specificStock();
  }
}

void Menus::specificStockSwitch(sharedStock &stock, char &opt) {
  Portifolio &userPortifolio = Portifolio::getPortifolio();
  if (!isLoop) {
    switch (opt) {
    case '1':
    case '2': {
      printInLanguage("\nInsert the Stock quantity\n>>> ",
                      "\nInsira a quantidade de ações\n>>> ");
      int32_t stockQuantity;
      cin >> stockQuantity;
      if (cin.fail()) {
        stockQuantity = 0;
        cin.clear();
        printInLanguage("Enter an valid value\n", "Insira um valor válido\n");
        sleep(std::chrono::milliseconds(MS_ERROR_SLEEP));
        return;
      }
      if (stockQuantity >= 0)
        if (opt == '1') {
          userPortifolio.buyStock(stock, stockQuantity);
          if ((stock->getPrice() * stockQuantity) >
              userPortifolio.get_MoneyInAccount())
            return;
          if (language == '1') {
            cout << stockQuantity << stock->getTicker()
                 << " stocks were purshased, each coasting "
                 << stock->getPrice() << "\nIn total, the cost was $"
                 << stock->getPrice() * stockQuantity << '\n';
          } else if (language == '2') {
            cout << "Foram compradas " << stockQuantity << " ações "
                 << stock->getTicker() << " saindo cada uma por "
                 << stock->getPrice() << "\nNo total ficou "
                 << stock->getPrice() * stockQuantity << '\n';
            SysFuncs funcManager;
            funcManager.pressEnterToContinue();
          } else
            exit(2);
          cin.clear();
          SysFuncs funcsManager;
          funcsManager.pressEnterToContinue();
        } else {
          userPortifolio.sellStock(stock, stockQuantity);
          if ((stock->getPrice() * stockQuantity) <=
              userPortifolio.get_MoneyInAccount())
            return;
          if (language == '1') {
            cout << stockQuantity << stock->getTicker()
                 << " stocks were sold, each coasting " << stock->getPrice()
                 << "\nIn total, the cost was $"
                 << stock->getPrice() * stockQuantity << '\n';
          } else if (language == '2') {
            cout << "Foram vendidas " << stockQuantity << " ações "
                 << stock->getTicker() << " saindo cada uma por R$"
                 << stock->getPrice() << "\nNo total ficou R$"
                 << stock->getPrice() * stockQuantity << '\n';
          } else
            exit(2);
          cin.clear();
          SysFuncs funcsManager;
          funcsManager.pressEnterToContinue();
        }
      else {
        printInLanguage(
            "Cannot buy negative quantity of stocks\n",
            "Impossivel comprar uma quantidade negativa de ações\n");
        sleep(std::chrono::milliseconds(MS_ERROR_SLEEP));
      }
      break;
    }
    case '\n': {
      return;
    }
    default: {
      printInLanguage("Invalid key\n", "Chave inválida\n");
      sleep(std::chrono::milliseconds(MS_ERROR_SLEEP));
      break;
    }
    }
  }
}

void Menus::fullPortifolioMenu() {
  SysFuncs funcsManager;
  Portifolio &portifolioInstance = Portifolio::getPortifolio();
  portifolioInstance.printFullPortifolio();
  funcsManager.pressEnterToContinue();
}

void Menus::enterSingleChar(char &input) {
  SysFuncs funcsManager;
  char temp = funcsManager.getSingleKey();
  isLoop = false;
  input = temp;
}

void Menus::allTransactionsMenu() {
  Portifolio &portifolioInstance = Portifolio::getPortifolio();
  SysFuncs funcsManager;
  const auto &allTransactions = portifolioInstance.getAllTransactions();
  for (const auto &transaction : allTransactions) {
    cout << transaction.first << "º ";
    printInLanguage("transaction: ", "transação: ");
    transaction.second.printTransaction();
  }
  funcsManager.pressEnterToContinue();
}
