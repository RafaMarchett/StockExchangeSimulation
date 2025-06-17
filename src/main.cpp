#include "../headers/Graphs.h"
#include "../headers/Market.h"
#include "../headers/Menus.h"
#include "../headers/Portifolio.h"
#include "../headers/Saver.h"
#include "../headers/Tick.h"
#include "../headers/header.hpp"

Tick *mainTick = nullptr;
Portifolio *mainPortifolio = nullptr;
Market *mainMarket = nullptr;

void firstInitialization(Market *&marketInstance, Tick *&tickInstance,
                         Portifolio *&portifolioInstance) {
  configureDouble();
  marketInstance = &Market::getMarket();
  vector<sharedStock> tempStocks = {
      make_shared<Stock>(30.42f, "RLS3", "Ralsey's Hat", "Clothing"),
      make_shared<Stock>(100.31f, "MEG3", "Major Explorer Group", "Research"),
      make_shared<Stock>(25.10f, "GLOB3", "GlobalTech Solutions", "Technology"),
      make_shared<Stock>(75.50f, "AFS3", "Apex Financial Services",
                         "Financial"),
      make_shared<Stock>(75.3, "BNTG3", "Backrooms Nonaligned Trade Group",
                         "Retail"),
      make_shared<Stock>(30.0f, "STRP3", "Stroustrup's Code", "Technology"),
      make_shared<Stock>(210.0f, "CHJK3", "Chicken Jockey", "Food"),
      make_shared<Stock>(11.80f, "DATA3", "SecureData Solutions", "Technology"),
      make_shared<Stock>(50.23, "PRIT3", "PrinTech Art 3D", "Technology"),
      make_shared<Stock>(124.24, "MYS3", "Mysticy Backrooms", "Backrooms")};
  marketInstance->startMarket(tempStocks);
  tickInstance = &Tick::getInstance();
  portifolioInstance = &Portifolio::getPortifolio();
  Menus::firstInitialization();
  portifolioInstance->add_moneyInAccount(1500.0);
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
        mainPortifolio->updatePortifolioHistory();
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
  srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::fstream File(fileName, std::ios::in | std::ios::ate);
  if (!File || File.tellg() == 0)
    firstInitialization(mainMarket, mainTick,
                        mainPortifolio); // New firstInitialization
  else
    loadInitialization(mainMarket, mainTick,
                       mainPortifolio); // Load File
  std::jthread currentMenu(Menus::homeMenu);
  mainLoop();
  return 0;
}
