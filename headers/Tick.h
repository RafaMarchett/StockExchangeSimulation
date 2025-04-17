#pragma once

#include "header.hpp"
#ifndef TICK
#define TICK

using namespace std::chrono;
#define sleep std::this_thread::sleep_for

class Tick
{
    public:
    void startProgram();

    private:
    void tickLoop();
    const size_t tickIntervalMS {100}; // TICK INTERVAL
    size_t getCurrentTimeMS(); 
    int currentTick{0};
};

#include "Tick.cpp"
#endif // TICK
