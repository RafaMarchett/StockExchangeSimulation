#include "../headers/Market.h"
#include "../headers/MarketEvents.h"
#include "../headers/Stock.h"
void Market::startMarket(vector<sharedStock> &tempStocks) {
  for (auto &stock : tempStocks) {
    if (!stock)
      cout << "ERROR TO INITIALIZE STOCK IN MARKET\n;";
    addNewStock(stock);
  }
}

bool Market::getStockOnScreen() const { return stocksOnScreen; }
vector<string> Market::getAllSectors() const { return allSectors; }
void Market::setStockOnScreen(bool newState) { stocksOnScreen = newState; }
void Market::setAllSectors(const vector<string> &inputString) {
  if (allSectors.empty()) {
    allSectors = inputString;
  }
}
size_t Market::getNumberOfStocks() { return _numberOfStocks; }

Market &Market::getMarket() {
  static Market mkt;
  return mkt;
}

void Market::updateAllStocksPrice() {
  marketEvents &marketEventsInstance = marketEvents::getMarketEvents();
  marketEventsInstance.generateRandomEvent();
  for (auto &stock : allStocks) {
    if (stock.second->getSector() ==
        marketEventsInstance.getCurrentEventSector()) {
      stock.second->randomPriceUpdate(
          marketEventsInstance.getBull_or_recessionMarket());
    }
    stock.second->randomPriceUpdate();
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
  allMembers.allSectors = allSectors;
  return allMembers;
}
void Market::setAllMembers(const _Market::allMembers &inputStruct) {
  stocksOnScreen = inputStruct.stocksOnScreen;
  _numberOfStocks = inputStruct._numberOfStocks;
  allStocks = inputStruct.allStocks;
  allSectors = inputStruct.allSectors;
}

sharedStock Market::findTicker(const string &inputString) {
  if (allStocks.find(inputString) != allStocks.end())
    return allStocks.find(inputString)->second;
  else
    return nullptr;
}
