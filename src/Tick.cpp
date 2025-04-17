#ifdef TICK

#include "Tick.h"
size_t Tick::getCurrentTimeMS() 
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Tick::tickLoop() 
{
    size_t lastTickMS = getCurrentTimeMS();
    while (1) 
    {
        size_t currentTimeMS = getCurrentTimeMS();
        
        bool passTick = currentTimeMS - lastTickMS >= tickIntervalMS;
        if (passTick) 
        {
            // TICK LOGIC

            lastTickMS = currentTimeMS;
        }

        size_t timeToNextTickMS = (lastTickMS + tickIntervalMS) - currentTimeMS;
        sleep(milliseconds(timeToNextTickMS));
    }
}

void Tick::startProgram()
{
    tickLoop();
}
#endif // TICK
