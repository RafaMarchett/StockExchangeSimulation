#pragma once
#include "header.hpp"
#ifndef MARKET
#define MARKET
class Stock;
using sharedStock = std::shared_ptr<Stock>;

namespace _Market {
struct allMembers {
  bool stocksOnScreen;
  size_t _numberOfStocks{0};
  std::unordered_map<string, sharedStock> allStocks;
  vector<string> allSectors;

  auto toTuple() {
    return std::tie(stocksOnScreen, _numberOfStocks, allStocks, allSectors);
  }
};
} // namespace _Market

class Market {
public:
  void addNewStock(sharedStock &);
  static Market &getMarket();
  void updateAllStocksPrice();
  inline void printAllStocks();
  size_t getNumberOfStocks();
  vector<string> getAllSectors() const;
  void setStockOnScreen(bool);
  bool getStockOnScreen() const;
  sharedStock findTicker(const string &);
  void applyMarketEvent(const string &);

  _Market::allMembers getAllMembers();
  void setAllMembers(const _Market::allMembers &);
  void startMarket(vector<sharedStock> &);

private:
  Market() = default;
  bool stocksOnScreen;
  void outputPointer_PrintStocks();
  size_t _numberOfStocks{0};
  std::unordered_map<string, sharedStock> allStocks;
  vector<string> allSectors;
};

#include "Stock.h"
void Market::printAllStocks() {
  cout << clear;
  printInLanguage("##### STOCK MARKET #####\n\n",
                  "##### MERCADO DE AÇÕES #####\n\n");

  for (auto &stock : allStocks) {
    stocksOnScreen = true;
    if (!stocksOnScreen) {
      return;
    }

    stock.second->printStockInMarket();
    cout << std::endl;
  }
}
#endif // MARKET
