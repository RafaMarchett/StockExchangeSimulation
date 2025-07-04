#pragma once
#include "Stock.h"
#include "header.hpp"
#ifndef PORTIFOLIO
#define PORTIFOLIO
typedef size_t transaction_number;

struct transactionData {
  string stockTicker;
  double stockValue;
  size_t stockCount;
  bool isBuy;

  auto toTuple() {
    return std::tie(stockTicker, stockValue, stockCount, isBuy);
  }
  inline void printTransaction() const {
    cout << '\n';
    if (isBuy)
      printInLanguage("PURCHASE ORDER", "ORDEM DE COMPRA");
    else
      printInLanguage("SALES ORDER", "ORDEM DE VENDA");
    cout << " | ";
    printInLanguage("Ticker: ", "Ticker: ");
    cout << stockTicker << " | ";
    printInLanguage("Unit price: ", "Preço unitário: ");
    cout << stockValue << " | ";
    printInLanguage("Quantity: ", "Quantidade: ");
    cout << stockCount << std::endl;
  }
};
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
  std::unordered_map<string, std::stack<double>> stockHistoryInPortifolio;
  std::stack<double> portifolioHistory;
  std::map<transaction_number, transactionData> allTransactions;
  double _moneyInAccount;
  double _totalMoney;

  auto toTuple() {
    return std::tie(fullPortifolio, _moneyInAccount, _totalMoney,
                    stockHistoryInPortifolio, allTransactions,
                    portifolioHistory);
  }
};
} // namespace _Portifolio

class Tick;
class Portifolio {
public:
  std::stack<double> getStockHistoryInPortifolio(const string &) const;
  std::stack<double> getPortifolioHistory() const;
  void printFullPortifolio() const;
  void buyStock(const sharedStock &, const size_t &);
  void sellStock(const sharedStock &, const size_t &);
  static Portifolio &getPortifolio();
  double get_MoneyInAccount() const;
  double get_TotalMoney() const;
  void updatePortifolioHistory();
  void newTransaction(const string &, const double &, const size_t &,
                      const bool &);
  std::map<transaction_number, transactionData> getAllTransactions() const;

  _Portifolio::allMembers getAllMembers();
  void setAllMembers(const _Portifolio::allMembers &);
  friend void firstInitialization(Market *&marketInstance, Tick *&tickInstance,
                                  Portifolio *&portifolioInstance);

  friend Portifolio &getPortifolio();

private:
  Portifolio() = default;
  void add_moneyInAccount(double);
  double calculateAveragePrice(const sharedStock &, double, int);
  void calculateTotalParticipation(const sharedStock &);
  std::stack<double> portifolioHistory;
  std::unordered_map<string, std::stack<double>> stockHistoryInPortifolio;

  std::unordered_map<string, stockData> fullPortifolio;
  std::map<transaction_number, transactionData> allTransactions;
  double _moneyInAccount{0.0f};
  double _totalMoney{0.0f};
};

#endif // PORTIFOLIO
