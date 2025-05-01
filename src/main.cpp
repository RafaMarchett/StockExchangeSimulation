
#include "../headers/Class1.h"
#include "../headers/Market.h"
#include "../headers/Menus.h"
#include "../headers/Portifolio.h"
#include "../headers/Saver.h"
#include "../headers/Tick.h"
#include "../headers/header.hpp"

#define TST 0
#define SAV 1
#define READ 1

int main(int agrc, char *argv[]) {
#if TST
  if (SAV) {
    Class1 a;
    a.setInt(10);
    a.setString("HAHAAHAHA");
    Saver s;
    auto allMembers = a.getAllMembers();
    s.saveClass(allMembers);
  }
  if (READ) {
    Class1 a;
    Saver s;
    _Class1::allMembers allMembers;

    s.readClass(allMembers);
    a.setInt(allMembers.outi);
    a.setString(allMembers.outh);
    a.hello();
  }
#else
  Tick mainTick = Tick::getInstance();
  configureFloat();
  size_t lastTickMS = mainTick.getCurrentTimeMS();
  Menus::firstInitialization();
  std::function<void()> currentMenu = Menus::homeMenu();
  Portifolio mainPortifolio = Portifolio::getPortifolio();
  Market mainMarket = Market::getMarket();
  while (1) {
    size_t currentTimeMS = mainTick.getCurrentTimeMS();

    bool passTick = currentTimeMS - lastTickMS >= mainTick.getTickIntervalMS();
    if (passTick) {
      // TICK LOGIC
      if (mainTick.getCurrentTick() % 10 == 0) {
        mainMarket.updateAllStocksPrice();
        currentMenu();
      }

      mainMarket.printAllStocks();
      mainTick.incrementTick();
      lastTickMS = currentTimeMS;
    }
    size_t timeToNextTickMS =
        (lastTickMS + mainTick.getTickIntervalMS()) - currentTimeMS;
    sleep(milliseconds(timeToNextTickMS));
  }
#endif
  return 0;
}
