#include "../headers/MarketEvents.h"
#include "../headers/Market.h"

string marketEvents::getCurrentEventSector() const {
  return currentEventSector;
}
Ternary marketEvents::getBull_or_recessionMarket() const {
  return bull_or_recessionMarket;
}
marketEvents &marketEvents::getMarketEvents() {
  static marketEvents marketEventsInstance;
  return marketEventsInstance;
}
_marketEvents::allMembers marketEvents::getAllMembers() {
  _marketEvents::allMembers allMembers;
  allMembers.currentEventSector = currentEventSector;
  allMembers.eventTime = eventTime;
  allMembers.bull_or_recessionMarket_value = bull_or_recessionMarket.get();
  allMembers.bull_or_recessionMarket = allMembers.bull_or_recessionMarket_value;

  return allMembers;
}
void marketEvents::setAllMembers(const _marketEvents::allMembers &inputStruct) {
  currentEventSector = inputStruct.currentEventSector;
  eventTime = inputStruct.eventTime;
  bull_or_recessionMarket = inputStruct.bull_or_recessionMarket_value;
}
void marketEvents::generateRandomEvent() {
  passTick();
  if (eventTime <= 0) {
    currentEventSector = "";
  }
  if (currentEventSector == "") {
    int randomSeedEvent = (rand() % 100) + 1;
    if (randomSeedEvent < 50) {
      currentEventSector = "";
      return;
    }
    Market &marketInstance = Market::getMarket();
    vector<string> allSectors = marketInstance.getAllSectors();
    int randomSector = rand() % allSectors.size();
    bull_or_recessionMarket = rand() % 2 - 1;
    eventTime = 300;
    if (bull_or_recessionMarket.get() == 0) {
      bull_or_recessionMarket = 1;
    }
    currentEventSector = allSectors[randomSector];
  }
}
void marketEvents::passTick() {
  if (eventTime > 0)
    eventTime--;
}
