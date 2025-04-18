#pragma once

#include "header.hpp"
#ifndef TICK
#define TICK

using namespace std::chrono;
#define sleep std::this_thread::sleep_for

class Tick
{
    public:
    size_t getCurrentTimeMS() const; 
    size_t getTickIntervalMS() const {return tickIntervalMS;} 
    private:
    const size_t tickIntervalMS {100}; // TICK INTERVAL
    int currentTick{0};
};

#include "../src/Tick.cpp"
#endif // TICK
