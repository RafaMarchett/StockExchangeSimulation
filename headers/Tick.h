#pragma once
#include "header.hpp"
#ifndef TICK
#define TICK

#define milliseconds std::chrono::milliseconds
#define seconds std::chrono::seconds
#define sleep std::this_thread::sleep_for

class Tick
{
    public:
    void passTick();

    // Cada tick vai ter 1 segundo
    
    private:
    int currentTick{0};
};

#include "../src/Tick.cpp"
#endif // TICK