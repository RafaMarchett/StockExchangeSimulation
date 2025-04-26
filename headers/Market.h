#pragma once
#include "header.hpp"
#ifndef MARKET
#define MARKET

class Stock;
using sharedStock = std::shared_ptr<Stock>;
class Market {
public:
  void addNewStock(sharedStock &);
  static Market &getMarket();
  void updateAllStocksPrice();
  void printAllStocks();
  size_t getNumberOfStocks();
  void setStockOnScreen(bool);

private:
  Market();
  bool stocksOnScreen;
  void outputPointer_PrintStocks();
  size_t _numberOfStocks{0};
  std::unordered_map<string, sharedStock> allStocks;
};

#include "../src/Market.cpp"
#endif // MARKET
