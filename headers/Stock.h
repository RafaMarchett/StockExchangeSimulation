#pragma once
#include "Market.h"
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
  void randomPriceUpdate();

  Stock(float, string, string);

private:
  float _price{0.0f};
  string _ticker, _companyName;
};

#include "../src/Stock.cpp"
#endif // STOCK
