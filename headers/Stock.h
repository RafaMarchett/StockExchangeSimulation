#pragma once
#include "Tick.h"
#include "header.hpp"
#ifndef STOCK
#define STOCK
class Market;
class Stock;
using sharedStock = std::shared_ptr<Stock>;

class Stock {
public:
  friend class Market;
  string getTicker() const;
  float getPrice() const;
  void setPrice(float);
  string getCompanyName() const;
  void randomPriceUpdate();
  void printStockInMarket();
  string getArrow();

  Stock(float, string, string);

private:
  float _price{0.0f};
  string _ticker, _companyName;
  vector<float> priceHistory;
};

#include "../src/Stock.cpp"
#endif // STOCK
