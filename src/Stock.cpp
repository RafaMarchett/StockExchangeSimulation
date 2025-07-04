#include "../headers/Stock.h"
#include "../headers/Market.h"

string Stock::getTicker() const { return _ticker; }
double Stock::getPrice() const { return _price; }
string Stock::getSector() const { return _sector; }
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

Stock::Stock(double price, string ticker, string companyName,
             string inputSector)
    : _price(price), _ticker(ticker), _companyName(companyName) {
  Market &marketInstance = Market::getMarket();
  auto allSectors = marketInstance.getAllSectors();
  for (auto &sector : allSectors) {
    if (sector == inputSector) {
      _sector = inputSector;
      return;
    }
  }
  std::cerr << "ERROR: Sector nonexistent\n";
  exit(1);
}

void Stock::randomPriceUpdate() {
  Ternary a;
  a = 0;
  randomPriceUpdate(a);
}

void Stock::randomPriceUpdate(Ternary eventInMarket) {
  double highOrDrop;
  if (eventInMarket.get() == 0) {
    highOrDrop = (rand() % 2 == 0 ? -0.89 : 1.0);
  }
  if (eventInMarket.get() == 1) {
    highOrDrop = 1.1;
  }
  if (eventInMarket.get() == -1) {
    highOrDrop = -0.925;
  }
  double randNumber = ((rand() % 6) + 1);

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
  allMembers._sector = _sector;
  allMembers.priceHistory = priceHistory;
  return allMembers;
}
void Stock::setAllMembers(const _Stock::allMembers &inputStruct) {
  _price = inputStruct._price;
  _ticker = inputStruct._ticker;
  _companyName = inputStruct._companyName;
  _sector = inputStruct._sector;
  priceHistory = inputStruct.priceHistory;
}
vector<double> Stock::getPriceHistory() { return priceHistory; }
