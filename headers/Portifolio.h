#pragma once
#include "Stock.h"
#include "header.hpp"
#ifndef PORTIFOLIO
#define PORTIFOLIO

struct stockData {
  size_t totalStocks{0};
  double averagePrice{0.0f};
  double totalParticipation{0.0f};

  auto toTuple() {
    return std::tie(totalStocks, averagePrice, totalParticipation);
  }
};
namespace _Portifolio {
struct allMembers {

  std::unordered_map<string, stockData> fullPortifolio;
  double _moneyInAccount;

  auto toTuple() { return std::tie(fullPortifolio, _moneyInAccount); }
};
} // namespace _Portifolio

class Tick;
class Portifolio {
public:
  void printFullPortifolio() const;
  void buyStock(const sharedStock &, const size_t &);
  void sellStock(const sharedStock &, const size_t &);
  static Portifolio &getPortifolio();
  double get_MoneyInAccount() const;

  _Portifolio::allMembers getAllMembers();
  void setAllMembers(const _Portifolio::allMembers &);
  friend void firstInitialization(Market *&marketInstance, Tick *&tickInstance,
                                  Portifolio *&portifolioInstance);

  void get_MoneyInAccount();
  friend Portifolio &getPortifolio();

private:
  Portifolio() = default;
  void add_moneyInAccount(double);
  double calculateAveragePrice(const sharedStock &, double, int);
  void calculateTotalParticipation(const sharedStock &);

  std::unordered_map<string, stockData> fullPortifolio;
  double _moneyInAccount{0.0f};
};

#endif // PORTIFOLIO
