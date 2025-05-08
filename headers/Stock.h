#pragma once
#include "header.hpp"
#ifndef STOCK
#define STOCK
class Market;
class Stock;
using sharedStock = std::shared_ptr<Stock>;

namespace _Stock {
struct allMembers {
  double _price{0.0f};
  string _ticker, _companyName;
  vector<double> priceHistory;

  auto toTuple() {
    return std::tie(_price, _ticker, _companyName, priceHistory);
  }
};
} // namespace _Stock

class Stock {
public:
  friend class Market;
  string getTicker() const;
  double getPrice() const;
  void setPrice(double);
  string getCompanyName() const;
  void randomPriceUpdate();
  void printStockInMarket();
  string getArrow();

  Stock(double, string, string);

  _Stock::allMembers getAllMembers();
  void setAllMembers(const _Stock::allMembers &);

private:
  double _price{0.0f};
  string _ticker, _companyName;
  vector<double> priceHistory;
};

#endif // STOCK
