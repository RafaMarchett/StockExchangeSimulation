#include "../headers/header.hpp"
#include "../headers/Tick.h"
#include <unordered_map>

int main(int agrc,char* argv[])
{
    Tick mainTick; 
    size_t lastTickMS = mainTick.getCurrentTimeMS();
    while (1) 
    {
        size_t currentTimeMS = mainTick.getCurrentTimeMS();
        
        bool passTick = currentTimeMS - lastTickMS >= mainTick.getTickIntervalMS();
        if (passTick) 
        {
            // TICK LOGIC

            lastTickMS = currentTimeMS;
        }

        size_t timeToNextTickMS = (lastTickMS + mainTick.getTickIntervalMS()) - currentTimeMS;
        sleep(milliseconds(timeToNextTickMS));
    }

    return 0;
}