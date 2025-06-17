#include "../headers/Market.h"
#include "../headers/Menus.h"
#include "../headers/Stock.h"
#include "../headers/SystemFunctions.h"
void Market::startMarket(vector<sharedStock> &tempStocks) {
  for (auto &stock : tempStocks) {
    if (!stock)
      cout << "ERROR TO INITIALIZE STOCK IN MARKET\n;";
    addNewStock(stock);
  }
}

void Market::outputPointer_PrintStocks() {
  string moveUp = "\x1B[" + std::to_string(getNumberOfStocks()) + "A";
  cout << moveUp << std::flush;
}
bool Market::getStockOnScreen() const { return stocksOnScreen; }
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

void Market::addNewStock(sharedStock &newStock) {
  if (newStock) {
    allStocks.emplace(newStock->getTicker(), std::move(newStock));
    _numberOfStocks = allStocks.size();
  }
}

_Market::allMembers Market::getAllMembers() {
  _Market::allMembers allMembers;
  allMembers._numberOfStocks = _numberOfStocks;
  allMembers.stocksOnScreen = stocksOnScreen;
  allMembers.allStocks = allStocks;
  return allMembers;
}
void Market::setAllMembers(const _Market::allMembers &inputStruct) {
  stocksOnScreen = inputStruct.stocksOnScreen;
  _numberOfStocks = inputStruct._numberOfStocks;
  allStocks = inputStruct.allStocks;
}

sharedStock Market::findTicker(const string &inputString) {
  if (allStocks.find(inputString) != allStocks.end())
    return allStocks.find(inputString)->second;
  else
    return nullptr;
}
void Market::applyMarketEvent(const string &inputSector) {
  int bull_or_recessionMarket = rand() % 2;
  for (auto &stock : allStocks) {
    if (stock.second->getSector() == inputSector) {
      // Mudar dinamica no change price da stock
    }
  }
}
