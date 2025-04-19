#include "../headers/header.hpp"
#include "../headers/Tick.h"
#include "../headers/Stock.h"
#include "../headers/Market.h"
#include "../headers/Menus.h"
#include "../headers/Portifolio.h"

int main(int agrc,char* argv[])
{
    size_t lastTickMS = mainTick.getCurrentTimeMS();

    while (1) 
    {
        size_t currentTimeMS = mainTick.getCurrentTimeMS();
        
        bool passTick = currentTimeMS - lastTickMS >= mainTick.getTickIntervalMS();
        if (passTick) 
        {
            // TICK LOGIC
            Menus::homeMenu();
            lastTickMS = currentTimeMS;
        }

        size_t timeToNextTickMS = (lastTickMS + mainTick.getTickIntervalMS()) - currentTimeMS;
        sleep(milliseconds(timeToNextTickMS));
    }

    return 0;
}