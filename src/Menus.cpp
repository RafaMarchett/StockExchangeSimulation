#include "../headers/Menus.h"
#include "../headers/Graphs.h"
#include "../headers/Market.h"
#include "../headers/MarketEvents.h"
#include "../headers/Portifolio.h"
#include "../headers/Saver.h"
#include "../headers/SystemFunctions.h"
#include "../headers/Tick.h"
inline std::atomic<bool> isLoop{false};
SysFuncs SysFuncsManager;
Menus::Menus() {}

void Menus::firstInitialization() { initializeLanguage(); }

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
  case '5': {
    marketNoticesMenu();
    break;
  }
  case '6': {
    saveAndExit();
    break;
  }

  default: {
    printInLanguage("\nInsert a valid option\n", "\nInsira uma opção válida\n");
  }
  }
  homeMenu();
}

void Menus::homeMenu() {
  char tempInput{'/'};
  cout << clear;
  printInLanguage(
      "Enter '1' to go to the \"Stock Market\" menu\nEnter '2' to go to the "
      "\"Single Stock\" menu\nEnter '3' to go to the \"Full Portifolio\" "
      "menu\nEnter '4' to go to the \"All Transactions\" menu\nEnter '5' to go "
      "to the \"Market News\" menu\nEnter '6' to close and save the program\n",
      "Insira '1' para ir ao menu \"Mercado de Ações\"\nInsira '2' para ir "
      "ao menu \"Ação única\"\nInsira '3' para ir ao menu \"Portifolio "
      "Completo\"\nInsira '4' para ir ao menu \"Todas as Transações\"\nInsira "
      "'5' para ir ao menu \"Noticias de Mercado\"\nInsira '6' para fechar e "
      "salvar o programa\n");

  tempInput = SysFuncsManager.getSingleKey();
  homeMenuOptions(tempInput);
  cout << ">>> " << std::flush;
  tempInput = SysFuncsManager.getSingleKey();
  homeMenuOptions(tempInput);
}

void Menus::allStocksMenu() {
  cout << clear;
  shared_ptr<Market> tempMarket(&Market::getMarket(), [](Market *) {});
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
  SysFuncsManager.pressEnterToContinue();
  isLoop = false;
}

void Menus::specificStock(sharedStock stock) {
  string inputTicker;
  auto &mkt = Market::getMarket();
  cout << clear;
  if (!stock) {
    printInLanguage(
        "Enter a stock ticker, or type \"exit\" to exit\n>>> ",
        "Insira o ticker de uma ação ou digite \"exit\" para sair\n>>> ");
    cin >> inputTicker;
    if (inputTicker == "exit")
      return;
    stock = mkt.findTicker(inputTicker);
  }
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
            "Stock\nEnter '3' to see the stock chart\nPress 'enter' to "
            "exit\n>>> ",
            "\nInsira '1' para comprar a ação\nInsira '2' para vender a "
            "ação\nInsira '3' para ver o grafico da ação\nPressione 'enter' "
            "para sair\n>>> ");
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
        SysFuncsManager.pressEnterToContinue();
        return;
      }
      if (stockQuantity >= 0)
        if (opt == '1') {
          if ((stock->getPrice() * stockQuantity) >
              userPortifolio.get_MoneyInAccount()) {
            return;
          }
          userPortifolio.buyStock(stock, stockQuantity);
          if (language == '1') {
            cout << stockQuantity << stock->getTicker()
                 << " stocks were purshased, each coasting "
                 << stock->getPrice() << "\nIn total, the cost was $"
                 << stock->getPrice() * stockQuantity << '\n';
            SysFuncsManager.pressEnterToContinue();
          } else if (language == '2') {
            cout << "Foram compradas " << stockQuantity << " ações "
                 << stock->getTicker() << " saindo cada uma por "
                 << stock->getPrice() << "\nNo total ficou "
                 << stock->getPrice() * stockQuantity << '\n';
            SysFuncsManager.pressEnterToContinue();
          } else {
            initializeLanguage();
          }
          cin.clear();
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
          } else {
            initializeLanguage();
          }
          cin.clear();
          SysFuncsManager.pressEnterToContinue();
        }
      else {
        printInLanguage(
            "Cannot buy negative quantity of stocks\n",
            "Impossivel comprar uma quantidade negativa de ações\n");
        SysFuncsManager.pressEnterToContinue();
      }
      break;
    }
    case '3': {
      Graphs graphsManager;
      char stopGraphLoop = '/';
      std::thread graphLoop([&]() {
        while (1) {
          if (stopGraphLoop == '\n')
            break;
          graphsManager.columnChart(stock->getPriceHistory());
          printInLanguage("Press 'enter' to continue\n",
                          "Pressione 'enter' para continuar\n");
          sleep(100ms);
        }
      });
      stopGraphLoop = SysFuncsManager.getSingleKey();
      graphLoop.join();
      specificStock(stock);
      break;
    }

    case '\n': {
      return;
    }
    default: {
      printInLanguage("Invalid key\n", "Chave inválida\n");
      SysFuncsManager.pressEnterToContinue();
      break;
    }
    }
  }
}

void Menus::fullPortifolioMenu() {
  Graphs graphsManager;
  Portifolio &portifolioInstance = Portifolio::getPortifolio();
  portifolioInstance.printFullPortifolio();
  printInLanguage("Insert '1' to se the wealth evolution chart or \n press "
                  "'Enter' to continue\n",
                  "Insira '1' para ver o grafico de evolução patrimonial, ou "
                  "\npressione 'Enter' para continuar\n");
  char input{'/'};
  input = SysFuncsManager.getSingleKey();
  if (input == '1') {
    if (portifolioInstance.getPortifolioHistory().empty()) {
      printInLanguage("The portifolio is empty\n", "O portifolio está vazio\n");
      SysFuncsManager.pressEnterToContinue();
      return;
    }
    char stopGraphLoop = '/';
    std::thread graphLoop([&]() {
      while (1) {
        if (stopGraphLoop == '\n')
          break;
        graphsManager.columnChart(portifolioInstance.getPortifolioHistory());
        printInLanguage("Press 'enter' to continue\n",
                        "Pressione 'enter' para continuar\n");
        cout << std::flush;
        sleep(100ms);
      }
    });
    stopGraphLoop = SysFuncsManager.getSingleKey();
    graphLoop.join();
    fullPortifolioMenu();
  }
  if (input == '\n')
    return;
}

void Menus::enterSingleChar(char &input) {
  char temp = SysFuncsManager.getSingleKey();
  isLoop = false;
  input = temp;
}

void Menus::allTransactionsMenu() {
  Portifolio &portifolioInstance = Portifolio::getPortifolio();
  const auto &allTransactions = portifolioInstance.getAllTransactions();
  cout << clear;
  for (const auto &transaction : allTransactions) {
    cout << transaction.first << "º ";
    printInLanguage("transaction: ", "transação: ");
    transaction.second.printTransaction();
  }
  SysFuncsManager.pressEnterToContinue();
}
void Menus::marketNoticesMenu() {
  marketEvents &marketEventsInstance = marketEvents::getMarketEvents();
  char stopNoticesLoop = '/';
  std::thread noticesLoop([&]() {
    while (1) {
      cout << clear;
      if (stopNoticesLoop == '\n')
        break;
      if (marketEventsInstance.getBull_or_recessionMarket().get() == 0) {
        cout << bold;
        printInLanguage("No unusual events are happening in the market\n",
                        "Nenhum evento atípico está acontecendo no mercado\n");
      } else if (marketEventsInstance.getBull_or_recessionMarket().get() == 1) {
        cout << bold << greenOutput;
        printInLanguage("The \"", "O setor \"");
        cout << marketEventsInstance.getCurrentEventSector();
        printInLanguage("\" sector is booming", "\"  está em alta");
      } else if (marketEventsInstance.getBull_or_recessionMarket().get() ==
                 -1) {
        cout << bold << redOutput;
        printInLanguage("The \"", "O setor \"");
        cout << marketEventsInstance.getCurrentEventSector();
        printInLanguage("\" sector is in crisis", "\"  está em crise");
      }
      cout << '\n' << noBold;
      printInLanguage("Press 'enter' to continue\n",
                      "Pressione 'enter' para continuar\n");
      cout << std::flush;
      sleep(100ms);
    }
  });
  stopNoticesLoop = SysFuncsManager.getSingleKey();
  noticesLoop.join();
}
void Menus::saveAndExit() {
  Saver::saveAllClasses(Market::getMarket(), Tick::getInstance(),
                        Portifolio::getPortifolio(),
                        marketEvents::getMarketEvents());
  exit(0);
  cout << noBold;
}
