#include "../headers/Portifolio.h"
#include "../headers/Market.h"
#include "../headers/SystemFunctions.h"
#include "../headers/Tick.h"
#include <compare>

Portifolio &Portifolio::getPortifolio() {
  static Portifolio portifolio;
  return portifolio;
}

std::map<transaction_number, transactionData>
Portifolio::getAllTransactions() const {
  return allTransactions;
}
void Portifolio::newTransaction(const string &inputTicker,
                                const double &inputPrice,
                                const size_t &stockCount,
                                const bool &inputIsBuy) {
  transaction_number lastTransactionNumber = allTransactions.end()->first;
  transactionData newTransaction = {inputTicker, inputPrice, stockCount,
                                    inputIsBuy};
  allTransactions.try_emplace(lastTransactionNumber + 1, newTransaction);
}
std::stack<double>
Portifolio::getStockHistoryInPortifolio(const string &stockTicker) const {
  return stockHistoryInPortifolio.at(stockTicker);
}
std::stack<double> Portifolio::getPortifolioHistory() const {
  return portifolioHistory;
}
double Portifolio::get_MoneyInAccount() const { return _moneyInAccount; }
double Portifolio::get_TotalMoney() const { return _totalMoney; }
double Portifolio::calculateAveragePrice(const sharedStock &buyedStock,
                                         double buyedPrice, int buyedQuantity) {
  auto &currentStockSecond =
      fullPortifolio.find(buyedStock->getTicker())->second;
  cout << "\nInp: " << (buyedQuantity * buyedPrice) << std::endl;
  cout << "\nTEMP: "
       << (currentStockSecond.totalParticipation + buyedPrice * buyedQuantity) /
              (buyedQuantity + currentStockSecond.totalStocks)
       << std::endl;
  return (currentStockSecond.totalParticipation + buyedPrice * buyedQuantity) /
         (buyedQuantity + currentStockSecond.totalStocks);
}

void Portifolio::calculateTotalParticipation(const sharedStock &stock) {
  auto &stockInPortifolioSecond =
      fullPortifolio.find(stock->getTicker())->second;
  stockInPortifolioSecond.totalParticipation =
      stockInPortifolioSecond.averagePrice *
      stockInPortifolioSecond.totalStocks;
}

void Portifolio::buyStock(const sharedStock &buyedStock,
                          const size_t &stockCount) {
  const double stockPrice = buyedStock->getPrice();
  if (buyedStock && stockCount > 0) {
    double buyedPrice = stockCount * stockPrice;
    if (_moneyInAccount < buyedPrice) {
      printInLanguage("You don't have enough money in the account\n",
                      "Você não tem dinheiro suficiente na conta\n");
      sleep(std::chrono::milliseconds(MS_ERROR_SLEEP));
      return;
    }

    if (fullPortifolio.find(buyedStock->getTicker()) != fullPortifolio.end()) {
      auto stockInPortifolio = fullPortifolio.find(buyedStock->getTicker());
      stockInPortifolio->second.averagePrice =
          calculateAveragePrice(buyedStock, stockPrice, stockCount);
      stockInPortifolio->second.totalStocks += stockCount;
    } else {
      stockData newStockData = {stockCount, stockPrice, buyedPrice};
      fullPortifolio.try_emplace(buyedStock->getTicker(), newStockData);
      std::stack<double> tempStack;
      tempStack.push(stockPrice);
      stockHistoryInPortifolio.try_emplace(buyedStock->getTicker(), tempStack);
    }
    _moneyInAccount -= buyedPrice * stockCount;
    calculateTotalParticipation(buyedStock);
    newTransaction(buyedStock->getTicker(), stockPrice, stockCount, true);
  }
}

void Portifolio::sellStock(const sharedStock &selledStock,
                           const size_t &stockCounter) {
  const double stockPrice = selledStock->getPrice();
  auto stocksInPortifolio = fullPortifolio.find(selledStock->getTicker());
  if (stocksInPortifolio != fullPortifolio.end() &&
      stocksInPortifolio->second.totalStocks >= stockCounter) {
    stocksInPortifolio->second.totalStocks -= stockCounter;
    calculateTotalParticipation(selledStock);
    _moneyInAccount += stockPrice * stockCounter;
    newTransaction(selledStock->getTicker(), stockPrice, stockCounter, false);
  } else {
    printInLanguage("You don't have enough stocks to sell",
                    "Você não possuí ações suficientes para vender\n");
    sleep(std::chrono::milliseconds(MS_ERROR_SLEEP));
  }
}
void Portifolio::printFullPortifolio() const {
  cout << clear;
  short counter{0};
  bool runLoop = true;
  std::thread printLoop([&]() {
    while (runLoop) {
      cout << clear;
      printInLanguage("Money in account: ", "Dinheiro na Conta: ");
      cout << get_MoneyInAccount() << "\n\n";
      for (auto &stock : fullPortifolio) {
        ++counter;
        if (language == '1') {

          cout << bold << stock.first << noBold
               << " Average Price: " << stock.second.averagePrice << ' '
               << (stock.second.averagePrice <
                           stockHistoryInPortifolio.at(stock.first).top()
                       ? upArrow
                       : downArrow)
               << " Stock Quantity: " << stock.second.totalStocks << "  TOTAL "
               << stock.second.totalParticipation << "\n Current Price: "
               << stockHistoryInPortifolio.at(stock.first).top() << bold
               << "\nTotal Money in Portifolio: " << noBold << _totalMoney
               << "\n\n";
        } else if (language == '2') {
          cout << bold << stock.first << noBold
               << " Preço médio: " << stock.second.averagePrice << ' '
               << (stock.second.averagePrice <
                           stockHistoryInPortifolio.at(stock.first).top()
                       ? upArrow
                       : downArrow)
               << " Quantidade de ações: " << stock.second.totalStocks << bold
               << "  TOTAL: " << stock.second.totalParticipation << noBold
               << "\n Preço Atual: "
               << stockHistoryInPortifolio.at(stock.first).top() << bold
               << "\nDinheiro total no portifolio: " << noBold << _totalMoney
               << "\n\n";
        } else
          exit(2);
      }
      printInLanguage("Press 'Enter' to continue...",
                      "Pressione 'Enter' para continuar...");
      cout << std::endl;
      sleep(std::chrono::milliseconds(100));
    }
  });
  SysFuncs funcManager;
  funcManager.pressEnterToContinue();
  runLoop = false;
  printLoop.join();
  if (counter == 0)
    printInLanguage("The Portifolio is empty\n", "O Portifolio está vazio\n");
}

_Portifolio::allMembers Portifolio::getAllMembers() {
  _Portifolio::allMembers allMembers;
  allMembers.fullPortifolio.insert(fullPortifolio.begin(),
                                   fullPortifolio.end());
  allMembers._moneyInAccount = _moneyInAccount;
  allMembers._totalMoney = _totalMoney;
  allMembers.stockHistoryInPortifolio.insert(stockHistoryInPortifolio.begin(),
                                             stockHistoryInPortifolio.end());
  allMembers.portifolioHistory = portifolioHistory;
  allMembers.allTransactions.insert(allTransactions.begin(),
                                    allTransactions.end());
  return allMembers;
}

void Portifolio::setAllMembers(const _Portifolio::allMembers &inputStruct) {
  fullPortifolio.insert(inputStruct.fullPortifolio.begin(),
                        inputStruct.fullPortifolio.end());
  _moneyInAccount = inputStruct._moneyInAccount;
  _totalMoney = inputStruct._totalMoney;
  stockHistoryInPortifolio.insert(inputStruct.stockHistoryInPortifolio.begin(),
                                  inputStruct.stockHistoryInPortifolio.end());
  portifolioHistory = inputStruct.portifolioHistory;
  allTransactions.insert(inputStruct.allTransactions.begin(),
                         inputStruct.allTransactions.end());
}
void Portifolio::add_moneyInAccount(double input) { _moneyInAccount += input; }
void Portifolio::updatePortifolioHistory() {
  Market &mkt = Market::getMarket();
  double tempTotalMoney{0.0f};
  for (auto &stock : fullPortifolio) {
    const auto &stockInHistory = stockHistoryInPortifolio.find(stock.first);
    if (stockInHistory != stockHistoryInPortifolio.end()) {
      stockInHistory->second.push(
          mkt.findTicker(stock.first)
              ->getPrice()); // Push current price in history
      tempTotalMoney += mkt.findTicker(stock.first)->getPrice();
    }
  }
  tempTotalMoney += _moneyInAccount;
  _totalMoney = tempTotalMoney;
  portifolioHistory.push(_totalMoney);
}
