#pragma once
#include "Stock.h"
#include "header.hpp"
#ifndef PORTIFOLIO
#define PORTIFOLIO

struct stockData {
  size_t totalStocks{0};
  float averagePrice{0.0f};
  float totalParticipation{0.0f};
};
namespace _Portifolio {
struct allMembers {

  std::unordered_map<string, stockData> fullPortifolio;
};
} // namespace _Portifolio

class Portifolio {
public:
  void printFullPortifolio() const;
  void buyStock(const sharedStock &, const size_t &);
  void sellStock(const sharedStock &, const size_t &);
  static Portifolio &getPortifolio();

  void setAllMembers(const _Portifolio::allMembers &);

private:
  struct stockData _stockData;
  float calculateAveragePrice(const sharedStock &, float, int);
  void calculateTotalParticipation(const sharedStock &);

  std::unordered_map<string, stockData> fullPortifolio;
};

#endif // PORTIFOLIO
