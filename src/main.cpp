
#include "../headers/Market.h"
#include "../headers/Menus.h"
#include "../headers/Portifolio.h"
#include "../headers/Saver.h"
#include "../headers/SystemFunctions.h"
#include "../headers/Tick.h"
#include "../headers/header.hpp"
#define TST 0
#define SAV 1
#define READ 1
void firstInitialization(Market *&marketInstance, Tick *&tickInstance,
                         Portifolio *&portifolioInstance) {
  configureFloat();
  marketInstance = &Market::getMarket();
  tickInstance = &Tick::getInstance();
  portifolioInstance = &Portifolio::getPortifolio();
  Menus::firstInitialization();
}
void loadInitialization(Market *&marketInstance, Tick *&tickInstance,
                        Portifolio *&portifolioInstance) {
  Market marketInstance2 = *marketInstance;
  Tick tickInstance2 = *tickInstance;
  Portifolio portifolioInstance2 = *portifolioInstance;
  Saver::readAllClasses(marketInstance2, tickInstance2, portifolioInstance2);
}

int main(int agrc, char *argv[]) {
#if TST
#else
  Tick *mainTick = nullptr;
  Portifolio *mainPortifolio = nullptr;
  Market *mainMarket = nullptr;

  std::fstream File(fileName, std::ios::in | std::ios::ate);
  if (!File || File.tellg() == 0)
    firstInitialization(mainMarket, mainTick,
                        mainPortifolio); // New firstInitialization
  else
    loadInitialization(mainMarket, mainTick,
                       mainPortifolio); // Load File
  size_t lastTickMS = mainTick->getCurrentTimeMS();
  std::function<void()> currentMenu = Menus::homeMenu();

  while (1) {
    size_t currentTimeMS = mainTick->getCurrentTimeMS();

    bool passTick = currentTimeMS - lastTickMS >= mainTick->getTickIntervalMS();
    if (passTick) {
      // TICK LOGIC
      if (mainTick->getCurrentTick() % 10 == 0) {
        mainMarket->updateAllStocksPrice();
        currentMenu();
      }

      mainMarket->printAllStocks();
      mainTick->incrementTick();
      lastTickMS = currentTimeMS;
    }
    size_t timeToNextTickMS =
        (lastTickMS + mainTick->getTickIntervalMS()) - currentTimeMS;
    sleep(milliseconds(timeToNextTickMS));
  }
#endif
  return 0;
}
