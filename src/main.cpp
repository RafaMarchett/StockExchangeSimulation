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

Tick *mainTick = nullptr;
Portifolio *mainPortifolio = nullptr;
Market *mainMarket = nullptr;

void firstInitialization(Market *&marketInstance, Tick *&tickInstance,
                         Portifolio *&portifolioInstance) {
  configureDouble();
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
void mainLoop() {
  size_t lastTickMS = mainTick->getCurrentTimeMS();

  while (1) {
    size_t currentTimeMS = mainTick->getCurrentTimeMS();

    bool passTick = currentTimeMS - lastTickMS >= mainTick->getTickIntervalMS();
    if (passTick) {
      // TICK LOGIC
      if (mainTick->getCurrentTick() % 10 == 0) {
        mainMarket->updateAllStocksPrice();
      }

      mainTick->incrementTick();
      lastTickMS = currentTimeMS;
    }
    size_t timeToNextTickMS =
        (lastTickMS + mainTick->getTickIntervalMS()) - currentTimeMS;
    sleep(milliseconds(timeToNextTickMS));
  }
}

int main(int agrc, char *argv[]) {
#if TST
#else

  std::fstream File(fileName, std::ios::in | std::ios::ate);
  if (!File || File.tellg() == 0)
    firstInitialization(mainMarket, mainTick,
                        mainPortifolio); // New firstInitialization
  else
    loadInitialization(mainMarket, mainTick,
                       mainPortifolio); // Load File
  // std::thread threadLoop(mainLoop);
  std::jthread currentMenu(Menus::homeMenu);
  mainLoop();
  // threadLoop.join();
#endif
  return 0;
}
