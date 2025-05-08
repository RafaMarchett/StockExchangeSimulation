#include "../headers/Portifolio.h"
#include "../headers/Tick.h"

Portifolio &Portifolio::getPortifolio() {
  static Portifolio portifolio;
  return portifolio;
}

double Portifolio::get_MoneyInAccount() const { return _moneyInAccount; }
double Portifolio::calculateAveragePrice(const sharedStock &buyedStock,
                                         double buyedPrice, int buyedQuantity) {
  auto currentStockSecond =
      fullPortifolio.find(buyedStock->getTicker())->second;
  return (currentStockSecond.averagePrice * currentStockSecond.totalStocks +
          buyedPrice * buyedQuantity) /
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
  if (buyedStock && stockCount > 0) {
    double buyedPrice = stockCount * buyedStock->getPrice();
    if (_moneyInAccount < buyedPrice) {
      printInLanguage("You don't have enough money in the account\n",
                      "Você não tem dinheiro suficiente na conta\n");
      sleep(std::chrono::milliseconds(MS_ERROR_SLEEP));
      return;
    }

    if (fullPortifolio.find(buyedStock->getTicker()) != fullPortifolio.end()) {
      auto stockInPortifolio = fullPortifolio.find(buyedStock->getTicker());
      stockInPortifolio->second.averagePrice =
          calculateAveragePrice(buyedStock, buyedPrice, stockCount);
      stockInPortifolio->second.totalStocks += stockCount;
    } else {
      stockData newStockData = {stockCount, buyedStock->getPrice(), buyedPrice};
      // fullPortifolio.insert({buyedStock->getTicker(), newStockData});
      fullPortifolio.try_emplace(buyedStock->getTicker(), newStockData);
    }
    _moneyInAccount -= buyedPrice;
    calculateTotalParticipation(buyedStock);
  }
}

void Portifolio::sellStock(const sharedStock &selledStock,
                           const size_t &stockCounter) {
  auto stocksInPortifolio = fullPortifolio.find(selledStock->getTicker());
  if (stocksInPortifolio != fullPortifolio.end() &&
      stocksInPortifolio->second.totalStocks >= stockCounter) {
    stocksInPortifolio->second.totalStocks -= stockCounter;
    calculateTotalParticipation(selledStock);
    _moneyInAccount += selledStock->getPrice() * stockCounter;
  } else {
    printInLanguage("You don't have enough stocks to sell",
                    "Você não possuí ações suficientes para vender\n");
    sleep(std::chrono::milliseconds(MS_ERROR_SLEEP));
  }
}
void Portifolio::printFullPortifolio() const {
  cout << clear;
  short counter{0};
  printInLanguage("Money in account: ", "Dinheiro na Conta: ");
  cout << get_MoneyInAccount() << '\n';
  for (auto &stock : fullPortifolio) {
    ++counter;
    if (language == '1') {
      cout << bold << stock.first << noBold
           << " Average Price: " << stock.second.averagePrice
           << " Stock Quantity: " << stock.second.totalStocks << "  TOTAL "
           << stock.second.totalParticipation << std::endl;
    } else if (language == '2') {
      cout << bold << stock.first << noBold
           << " Preço médio: " << stock.second.averagePrice
           << " Quantidade: " << stock.second.totalStocks << bold
           << "   TOTAL: " << stock.second.totalParticipation << noBold
           << std::endl;
    } else
      exit(2);
  }
  if (counter == 0)
    printInLanguage("The Portifolio is empty\n", "O Portifolio está vazio\n");
}

_Portifolio::allMembers Portifolio::getAllMembers() {
  _Portifolio::allMembers allMembers;
  allMembers.fullPortifolio.insert(fullPortifolio.begin(),
                                   fullPortifolio.end());
  allMembers._moneyInAccount = _moneyInAccount;
  return allMembers;
}

void Portifolio::setAllMembers(const _Portifolio::allMembers &inputStruct) {
  fullPortifolio.insert(inputStruct.fullPortifolio.begin(),
                        inputStruct.fullPortifolio.end());
  _moneyInAccount = inputStruct._moneyInAccount;
}
void Portifolio::add_moneyInAccount(double input) { _moneyInAccount += input; }
