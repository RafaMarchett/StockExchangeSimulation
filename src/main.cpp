
#include "../headers/Market.h"
#include "../headers/Menus.h"
#include "../headers/Portifolio.h"
#include "../headers/Tick.h"
#include "../headers/header.hpp"

int main(int agrc, char *argv[]) {
  Tick mainTick = Tick::getInstance();
  configureFloat();
  size_t lastTickMS = mainTick.getCurrentTimeMS();
  Menus::homeMenu();

  Portifolio mainPortifolio = Portifolio::getPortifolio();
  Market mainMarket = Market::getMarket();
  size_t tickCounter{0};
  while (1) {
    size_t currentTimeMS = mainTick.getCurrentTimeMS();

    bool passTick = currentTimeMS - lastTickMS >= mainTick.getTickIntervalMS();
    if (passTick) {
      ++tickCounter;
      lastTickMS = currentTimeMS;
    }
    size_t timeToNextTickMS =
        (lastTickMS + mainTick.getTickIntervalMS()) - currentTimeMS;
    sleep(milliseconds(timeToNextTickMS));
  }

  return 0;
}
