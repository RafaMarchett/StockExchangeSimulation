#pragma once
#include "Stock.h"
#include "header.hpp"
#ifndef PORTIFOLIO
#define PORTIFOLIO
class Portifolio {
public:
  void printFullPortifolio() const;
  void buyStock(const sharedStock &, const size_t &);
  void sellStock(const sharedStock &, const size_t &);
  static Portifolio &getPortifolio();

private:
  struct stockData {
    size_t totalStocks;
    float averagePrice;
    float totalParticipation = totalStocks * averagePrice;
  };
  float calculateAveragePrice(const sharedStock &, float, int);
  void calculateTotalParticipation(const sharedStock &);

  std::unordered_map<string, stockData> fullPortifolio;
};

#include "../src/Portifolio.cpp"
#endif // PORTIFOLIO
