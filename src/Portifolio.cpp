#include "../headers/Portifolio.h"

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
    if (!(_moneyInAccount >= buyedPrice)) {
      printInLanguage("You don't have enough money in the account\n",
                      "Você não tem dinheiro suficiente na conta\n");
      return;
    }

    if (fullPortifolio.find(buyedStock->getTicker()) != fullPortifolio.end()) {
      auto stockInPortifolio = fullPortifolio.find(buyedStock->getTicker());
      stockInPortifolio->second.averagePrice =
          calculateAveragePrice(buyedStock, buyedPrice, stockCount);
      stockInPortifolio->second.totalStocks += stockCount;
    } else {
      fullPortifolio.insert(
          {buyedStock->getTicker(), {stockCount, buyedPrice}});
    }
    calculateTotalParticipation(buyedStock);
  }
}

void Portifolio::sellStock(const sharedStock &selledStock,
                           const size_t &stockCounter) {
  auto &totalStocksInPortifolio =
      fullPortifolio.find(selledStock->getTicker())->second.totalStocks;
  if (totalStocksInPortifolio >= stockCounter && selledStock) {
    totalStocksInPortifolio -= stockCounter;
    calculateTotalParticipation(selledStock);
    _moneyInAccount += selledStock->getPrice() * stockCounter;
  } else {
    printInLanguage("You don't have enough stocks to sell",
                    "Você não possuí ações suficientes para vender\n");
  }
}
void Portifolio::printFullPortifolio() const {
  cout << clear;
  for (auto &stock : fullPortifolio) {
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
