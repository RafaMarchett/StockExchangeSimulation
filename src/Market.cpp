#ifdef MARKET
#include "../headers/Market.h"
#include "../headers/Stock.h"
Market::Market() {
  sharedStock tempStocks[] = {
      make_shared<Stock>(30.42f, "RLS3", "Ralsey's Hat"),
      make_shared<Stock>(100.31f, "MEG3", "Major Explorer Group"),
      make_shared<Stock>(25.10f, "GLOB3", "GlobalTech Solutions"),
      make_shared<Stock>(75.50f, "AFS3", "Apex Financial Services"),
      make_shared<Stock>(75.3, "BNTG3", "Backrooms Nonaligned Trade Group"),
      make_shared<Stock>(30.0f, "STRP3", "Stroustrup's Code"),
      make_shared<Stock>(210.0f, "CHJK3", "Chicken Jockey"),
      make_shared<Stock>(11.80f, "DATA3", "SecureData Solutions"),
      make_shared<Stock>(50.23, "PRIT3", "PrinTech Art 3D"),
      make_shared<Stock>(124.24, "MYS3", "Mysticy Backrooms")};

  for (auto &stock : tempStocks) {
    if (!stock)
      cout << "ERROR\n;";
    addNewStock(stock);
  }
}

void Market::outputPointer_PrintStocks() {
  string moveUp = "\x1B[" + std::to_string(getNumberOfStocks()) + "A";
  cout << moveUp << std::flush;
}
void Market::setStockOnScreen(bool newState) { stocksOnScreen = newState; }
size_t Market::getNumberOfStocks() { return _numberOfStocks; }

Market &Market::getMarket() {
  static Market mkt;
  return mkt;
}

void Market::updateAllStocksPrice() {
  for (auto &it : allStocks) {
    it.second->randomPriceUpdate();
  }
}

void Market::printAllStocks() {
  if (stocksOnScreen) {
    outputPointer_PrintStocks();

    for (auto &stock : allStocks) {
      stocksOnScreen = true;
      if (!stocksOnScreen)
        return;

      stock.second->printStockInMarket();
      cout << '\n';
    }
  }
}
void Market::addNewStock(sharedStock &newStock) {
  if (newStock) {
    allStocks.emplace(newStock->getTicker(), std::move(newStock));
    _numberOfStocks = allStocks.size();
  }
}
#endif // MARKET
