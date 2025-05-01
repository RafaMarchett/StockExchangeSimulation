#pragma once
#include "Tick.h"
#include "header.hpp"
#ifndef STOCK
#define STOCK
class Market;
class Stock;
using sharedStock = std::shared_ptr<Stock>;

namespace _Stock {
struct allMembers {
  float _price{0.0f};
  string _ticker, _companyName;
  vector<float> priceHistory;

  auto toTuple() {
    return std::tie(_price, _ticker, _companyName, priceHistory);
  }
};
} // namespace _Stock

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

  void setAllMembers(const _Stock::allMembers &);

private:
  float _price{0.0f};
  string _ticker, _companyName;
  vector<float> priceHistory;
};

#endif // STOCK
