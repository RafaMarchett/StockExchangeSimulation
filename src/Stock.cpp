#include "../headers/Stock.h"
#include "../headers/Market.h"

string Stock::getTicker() const { return _ticker; }
double Stock::getPrice() const { return _price; }
void Stock::setPrice(double price) {
  _price = price;
  priceHistory.insert(priceHistory.end(), price);
}
string Stock::getArrow() {
  size_t &&Size = priceHistory.size();
  size_t &&lastElement{Size - 1}, secondlastElement{Size - 2};
  if (Size >= 2) {
    if (priceHistory.at(lastElement) >= priceHistory.at(secondlastElement)) {
      return upArrow;
    } else {
      return downArrow;
    }
  } else
    return "";
}
string Stock::getCompanyName() const { return _companyName; }

Stock::Stock(double price, string ticker, string companyName)
    : _price(price), _ticker(ticker), _companyName(companyName) {}

void Stock::randomPriceUpdate() {
  srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  double highOrDrop = (rand() % 2 == 0 ? -0.89 : 1.0);
  double randNumber = ((rand() % 8) + 1);

  randNumber *= highOrDrop;
  randNumber += 100;
  randNumber /= 100;
  setPrice(getPrice() * randNumber);
}

void Stock::printStockInMarket() {
  cout << setw(40) << getCompanyName() << " | " << setw(7) << getTicker()
       << " | " << setw(7) << getPrice() << " | " << getArrow();
}

_Stock::allMembers Stock::getAllMembers() {
  _Stock::allMembers allMembers;
  allMembers._price = _price;
  allMembers._ticker = _ticker;
  allMembers._companyName = _companyName;
  allMembers.priceHistory = priceHistory;
  return allMembers;
}
void Stock::setAllMembers(const _Stock::allMembers &inputStruct) {
  _price = inputStruct._price;
  _ticker = inputStruct._ticker;
  _companyName = inputStruct._companyName;
  priceHistory = inputStruct.priceHistory;
}
