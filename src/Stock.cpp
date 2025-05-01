#include "../headers/Stock.h"
#include "../headers/Market.h"

string Stock::getTicker() const { return _ticker; }
float Stock::getPrice() const { return _price; }
void Stock::setPrice(float price) {
  _price = price;
  priceHistory.insert(priceHistory.begin(), price);
}
string Stock::getArrow() {
  size_t Size = priceHistory.size();
  if (Size >= 2) {
    if (priceHistory.at(Size - 1) >= priceHistory.at(Size - 2)) {
      return upArrow;
    } else {
      return downArrow;
    }
  } else
    return "";
}
string Stock::getCompanyName() const { return _companyName; }

Stock::Stock(float price, string ticker, string companyName)
    : _price(price), _ticker(ticker), _companyName(companyName) {}

void Stock::randomPriceUpdate() {
  srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  float highOrDrop = (rand() % 2 == 0 ? -0.89 : 1.0);
  float randNumber = ((rand() % 8) + 1);

  randNumber *= highOrDrop;
  randNumber += 100;
  randNumber /= 100;
  setPrice(getPrice() * randNumber);
}

void Stock::printStockInMarket() {
  cout << setw(40) << getCompanyName() << " | " << setw(7) << getTicker()
       << " | " << setw(7) << getPrice() << " | " << getArrow();
}

void Stock::setAllMembers(const _Stock::allMembers &inputStruct) {
  _price = inputStruct._price;
  _ticker = inputStruct._ticker;
  _companyName = inputStruct._companyName;
  priceHistory = inputStruct.priceHistory;
}
