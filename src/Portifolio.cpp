#include "../headers/Portifolio.h"

Portifolio &Portifolio::getPortifolio() {
  static Portifolio portifolio;
  return portifolio;
}

float Portifolio::calculateAveragePrice(const sharedStock &buyedStock,
                                        float buyedPrice, int buyedQuantity) {
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
    if (fullPortifolio.find(buyedStock->getTicker()) != fullPortifolio.end()) {
      auto stockInPortifolio = fullPortifolio.find(buyedStock->getTicker());
      stockInPortifolio->second.averagePrice =
          calculateAveragePrice(buyedStock, buyedStock->getPrice(), stockCount);
      stockInPortifolio->second.totalStocks += stockCount;
    } else {
      fullPortifolio.insert(
          {buyedStock->getTicker(), {stockCount, buyedStock->getPrice()}});
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
  } else {
    cout << "Você não possuí ações suficientes para vender\n";
  }
}
void Portifolio::printFullPortifolio() const {
  for (auto &stock : fullPortifolio) {
    cout << bold << stock.first << noBold
         << " Preço médio: " << stock.second.averagePrice
         << " Quantidade: " << stock.second.totalStocks << bold
         << "   TOTAL: " << stock.second.totalParticipation << noBold << '\n';
  }
}

_Portifolio::allMembers Portifolio::getAllMembers() {
  _Portifolio::allMembers allMembers;
  allMembers.fullPortifolio.insert(fullPortifolio.begin(),
                                   fullPortifolio.end());
  return allMembers;
}

void Portifolio::setAllMembers(const _Portifolio::allMembers &inputStruct) {
  fullPortifolio.insert(inputStruct.fullPortifolio.begin(),
                        inputStruct.fullPortifolio.end());
}
