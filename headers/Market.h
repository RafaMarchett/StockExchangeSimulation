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

  auto toTuple() {
    return std::tie(stocksOnScreen, _numberOfStocks, allStocks);
  }
};
} // namespace _Market

class Market {
public:
  void addNewStock(sharedStock &);
  static Market &getMarket();
  void updateAllStocksPrice();
  void printAllStocks();
  size_t getNumberOfStocks();
  void setStockOnScreen(bool);
  bool getStockOnScreen() const;

  _Market::allMembers getAllMembers();
  void setAllMembers(const _Market::allMembers &);

private:
  Market();
  bool stocksOnScreen;
  void outputPointer_PrintStocks();
  size_t _numberOfStocks{0};
  std::unordered_map<string, sharedStock> allStocks;
};

#endif // MARKET
