#pragma once
#include "Stock.h"
#include "header.hpp"
#ifndef PORTIFOLIO
#define PORTIFOLIO

struct stockData {
  size_t totalStocks{0};
  float averagePrice{0.0f};
  float totalParticipation{0.0f};

  auto toTuple() {
    return std::tie(totalStocks, averagePrice, totalParticipation);
  }
};
namespace _Portifolio {
struct allMembers {

  std::unordered_map<string, stockData> fullPortifolio;

  auto toTuple() { return std::tie(fullPortifolio); }
};
} // namespace _Portifolio

class Portifolio {
public:
  void printFullPortifolio() const;
  void buyStock(const sharedStock &, const size_t &);
  void sellStock(const sharedStock &, const size_t &);
  static Portifolio &getPortifolio();

  _Portifolio::allMembers getAllMembers();
  void setAllMembers(const _Portifolio::allMembers &);

private:
  struct stockData _stockData;
  float calculateAveragePrice(const sharedStock &, float, int);
  void calculateTotalParticipation(const sharedStock &);

  std::unordered_map<string, stockData> fullPortifolio;
};

#endif // PORTIFOLIO
