#ifdef TICK

#include "../headers/Tick.h"
size_t Tick::getCurrentTimeMS() const 
{
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

#endif // TICK
