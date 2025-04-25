// #ifdef STOCK
#include "../headers/Stock.h"

string Stock::getTicker() const { return _ticker; }
float Stock::getPrice() const { return _price; }
void Stock::setPrice(float price) { _price = price; }

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
// #endif // STOCK
