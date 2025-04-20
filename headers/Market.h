#pragma once
#include "header.hpp"
#include "Stock.h"
#ifndef MARKET
#define MARKET

class Market
{
public:
  Market();
  void addNewStock(uniqueStock&);
private:
  std::unordered_map<string,uniqueStock> allStocks;
}mainMarket;

#include "../src/Market.cpp"
#endif // MARKET