#pragma once
#include "Stock.h"
#include "header.hpp"
#ifndef MARKET
#define MARKET
class Stock;
class Market {
public:
  void addNewStock(sharedStock &);
  static Market &getMarket();
  void updateAllStocksPrice();

private:
  Market();
  std::unordered_map<string, sharedStock> allStocks;
};

#include "../src/Market.cpp"
#endif // MARKET
