#pragma once
#include "header.hpp"
#include "Stock.h"
#ifndef MARKET
#define MARKET

class Market
{
public:
  Market();
  void addNewStock(std::unique_ptr<Stock>&);
private:
  std::unordered_map<std::string,std::unique_ptr<Stock>> allStocks;
}mainMarket;

#include "../src/Market.cpp"
#endif // MARKET