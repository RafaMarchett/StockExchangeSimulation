#ifdef TICK

#include "../headers/Tick.h"
void Tick::passTick()
{
  sleep(seconds{1});
  ++currentTick;
}

#endif // TICK